#include "core.hpp"
#include "il2cpp.hpp"

#include "hooks/dispatch_message.hpp"
#include "hooks/present.hpp"
#include "hooks/resize_buffers.hpp"

#include "features/aimbot.hpp"
#include "features/user_interface.hpp"
#include "features/visuals.hpp"

namespace rust
{

std::uintptr_t m_unity_player = 0;
std::uintptr_t m_game_assembly = 0;
std::uintptr_t m_game_overlay_renderer = 0;

D3D11SwapChain* m_d3d11_swap_chain = nullptr;
IDXGISwapChain* m_swap_chain = nullptr;

SteamUser32* m_steam_user32 = nullptr;

memory::VFTableHook::Unique m_swap_chain_hook = { };

std::uintptr_t m_dispatch_message = 0;

std::uintptr_t m_present = 0;
std::uintptr_t m_resize_buffers = 0;

SteamUser32* GetSteamUser32()
{
	const auto address = memory::ScanImage( m_game_overlay_renderer, SECURE( "80 3D ? ? ? ? ? 74 10 8D 41 F0" ) );

	if( !memory::IsAddressValid( address ) )
	{
		TRACE( "%s: memory::ScanImage( ... ) error!", ATOM_FUNCTION );
		return nullptr;
	}

	const auto user32 = memory::GetAbsoluteAddress( address, 2 ) + 1;

	if( !memory::IsAddressValid( user32 ) )
	{
		TRACE( "%s: memory::GetAbsoluteAddress( 0x%016llX, 2 ) error!", ATOM_FUNCTION, address );
		return nullptr;
	}

	return reinterpret_cast< SteamUser32* >( user32 );
}

bool Create()
{
	auto& renderer = graphics::Renderer::Instance();

	auto& aimbot = features::Aimbot::Instance();
	auto& user_interface = features::UserInterface::Instance();
	auto& visuals = features::Visuals::Instance();

	m_unity_player = win32::GetImage( HASH( L"UnityPlayer.dll" ) );

	if( !memory::IsAddressValid( m_unity_player ) )
	{
		TRACE( "%s: win32::GetImage( ... ) error!", ATOM_FUNCTION );
		return false;
	}

	m_game_assembly = win32::GetImage( HASH( L"GameAssembly.dll" ) );

	if( !memory::IsAddressValid( m_game_assembly ) )
	{
		TRACE( "%s: win32::GetImage( ... ) error!", ATOM_FUNCTION );
		return false;
	}

	m_game_overlay_renderer = win32::GetImage( HASH( L"GameOverlayRenderer64.dll" ) );

	if( !memory::IsAddressValid( m_game_overlay_renderer ) )
	{
		TRACE( "%s: win32::GetImage( ... ) error!", ATOM_FUNCTION );
		return false;
	}

	if( !CreateIL2CPP() )
	{
		TRACE( "%s: CreateIL2CPP() error!", ATOM_FUNCTION );
		return false;
	}

	m_d3d11_swap_chain = GetD3D11SwapChain();

	if( !memory::IsAddressValid( m_d3d11_swap_chain ) )
	{
		TRACE( "%s: GetD3D11SwapChain() error!", ATOM_FUNCTION );
		return false;
	}

	m_swap_chain = m_d3d11_swap_chain->GetSwapChain();

	if( !memory::IsAddressValid( m_swap_chain ) )
	{
		TRACE( "%s: D3D11SwapChain::GetSwapChain() error!", ATOM_FUNCTION );
		return false;
	}

	m_steam_user32 = GetSteamUser32();

	if( !memory::IsAddressValid( m_steam_user32 ) )
	{
		TRACE( "%s: GetSteamUser32() error!", ATOM_FUNCTION );
		return false;
	}

	if( !renderer.Create( m_swap_chain ) )
	{
		TRACE( "%s: Renderer::Create( ... ) error!", ATOM_FUNCTION );
		return false;
	}

	if( !user_interface.Create() )
	{
		TRACE( "%s: UserInterface::Create() error!", ATOM_FUNCTION );
		return false;
	}

	m_dispatch_message = m_steam_user32->DispatchMessageA;
	
	if( memory::IsAddressValid( m_dispatch_message ) )
	{
		// 
		// hook pointer in GameOverlayRenderer64.dll
		// 
		m_steam_user32->DispatchMessageA = memory::ToAddress( &hooks::DispatchMessageA );
	}

	m_swap_chain_hook = std::make_unique< memory::VFTableHook >( m_swap_chain );

	if( m_swap_chain_hook )
	{
		m_present = m_swap_chain_hook->Get< 8 >();
		m_resize_buffers = m_swap_chain_hook->Get< 13 >();

		m_swap_chain_hook->Hook( &hooks::Present, 8 );
		m_swap_chain_hook->Hook( &hooks::ResizeBuffers, 13 );
	}

	return true;
}

void Destroy()
{
	auto& renderer = graphics::Renderer::Instance();

	if( memory::IsAddressValid( m_steam_user32 ) )
	{
		// 
		// restore pointer in GameOverlayRenderer64.dll
		// 
		m_steam_user32->DispatchMessageA = m_dispatch_message;
		m_steam_user32 = nullptr;
	}

	m_swap_chain_hook.reset();

	renderer.Destroy();

	m_swap_chain = nullptr;
	m_d3d11_swap_chain = nullptr;
	m_game_assembly = 0;
	m_unity_player = 0;
}

D3D11SwapChain* GetD3D11SwapChain()
{
	const auto address = memory::ScanImage( m_unity_player, SECURE( "48 8B 3D ? ? ? ? 45 8B E1 48 8B CF" ) );

	if( !memory::IsAddressValid( address ) )
	{
		TRACE( "%s: memory::ScanImage( ... ) error!", ATOM_FUNCTION );
		return nullptr;
	}

	const auto pointer = memory::GetAbsoluteAddress( address, 3 );

	if( !memory::IsAddressValid( pointer ) )
	{
		TRACE( "%s: memory::GetAbsoluteAddress( ... ) error!", ATOM_FUNCTION );
		return nullptr;
	}

	return memory::Dereference< D3D11SwapChain* >( pointer );
}

const Il2CppClass* FindClass( const Il2CppImage* image, const char* name_space, const char* name )
{
	return il2cpp_class_from_name( image, name_space, name );
}

const Il2CppClass* FindClass( const char* name_space, const char* name )
{
	const auto domain = il2cpp_domain_get();
	
	if( memory::IsAddressValid( domain ) )
	{
		std::size_t count = 0;
		const auto assemblies = il2cpp_domain_get_assemblies( domain, &count );
		
		if( memory::IsAddressValid( assemblies ) )
		{
			for( std::size_t index = 0; index < count; index++ )
			{
				const auto assembly = assemblies[ index ];

				if( memory::IsAddressValid( assembly ) )
				{
					const auto image = il2cpp_assembly_get_image( assembly );
					
					if( memory::IsAddressValid( image ) )
					{
						const auto instance = FindClass( image, name_space, name );

						if( memory::IsAddressValid( instance ) )
						{
							return instance;
						}
					}
				}
			}
		}
		else
		{
			TRACE( "%s: il2cpp_domain_get_assemblies( ... ) error!", ATOM_FUNCTION );
		}
	}
	else
	{
		TRACE( "%s: il2cpp_domain_get() error!", ATOM_FUNCTION );
	}

	return nullptr;
}

const FieldInfo* FindField( const Il2CppClass* object, std::uint64_t name_hash )
{
	auto super = object;

	while( memory::IsAddressValid( super ) )
	{
		auto iterator = static_cast< void* >( nullptr );
		auto field = il2cpp_class_get_fields( super, &iterator );

		while( memory::IsAddressValid( field ) )
		{
			const auto name = il2cpp_field_get_name( field );

			if( memory::IsAddressValid( name ) )
			{
				if( constant::Hash( name, true ) == name_hash )
				{
					return field;
				}
			}

			field = il2cpp_class_get_fields( super, &iterator );
		}

		super = super->parent;
	}

	return nullptr;
}

const PropertyInfo* FindProperty( const Il2CppClass* object, std::uint64_t name_hash )
{
	auto super = object;

	while( memory::IsAddressValid( super ) )
	{
		auto iterator = static_cast< void* >( nullptr );
		auto prop = il2cpp_class_get_properties( super, &iterator );

		while( memory::IsAddressValid( prop ) )
		{
			const auto name = il2cpp_property_get_name( prop );

			if( memory::IsAddressValid( name ) )
			{
				if( constant::Hash( name, true ) == name_hash )
				{
					return prop;
				}
			}

			prop = il2cpp_class_get_properties( super, &iterator );
		}

		super = super->parent;
	}

	return nullptr;
}

const MethodInfo* FindMethod( const Il2CppClass* object, std::uint64_t name_hash )
{
	return nullptr;
}

} // namespace rust

/*
class Aimbot : public core::Singleton< Aimbot >
{
public:
	void StepConstant( Vector3& rotation )
	{
		const auto pitch = 30.f;
		const auto yaw = 30.f;

		auto rotation_step = ( rotation - m_angles );
		// rotation_step.Normalize();

		if( pitch > 0.f )
		{
			auto factor_pitch = ( pitch / 100.f );

			if( rotation_step[ 0 ] < 0.f )
			{
				if( factor_pitch > std::abs( rotation_step[ 0 ] ) )
				{
					factor_pitch = std::abs( rotation_step[ 0 ] );
				}

				rotation[ 0 ] = m_angles[ 0 ] - factor_pitch;
			}
			else
			{
				if( factor_pitch > rotation_step[ 0 ] )
				{
					factor_pitch = rotation_step[ 0 ];
				}

				rotation[ 0 ] = m_angles[ 0 ] + factor_pitch;
			}
		}

		if( yaw > 0.f )
		{
			auto factor_yaw = ( yaw / 100.f );

			if( rotation_step[ 1 ] < 0.f )
			{
				if( factor_yaw > std::abs( rotation_step[ 1 ] ) )
				{
					factor_yaw = std::abs( rotation_step[ 1 ] );
				}

				rotation[ 1 ] = m_angles[ 1 ] - factor_yaw;
			}
			else
			{
				if( factor_yaw > rotation_step[ 1 ] )
				{
					factor_yaw = rotation_step[ 1 ];
				}

				rotation[ 1 ] = m_angles[ 1 ] + factor_yaw;
			}
		}
	}

	void StepDecreasing( Vector3& rotation )
	{
		const auto pitch = 8.f;
		const auto yaw = 8.f;

		auto rotation_step = ( rotation - m_angles );
		rotation_step.Normalize();

		if( pitch > 0.f )
		{
			rotation[ 0 ] = m_angles[ 0 ] + ( rotation_step[ 0 ] / pitch );
		}

		if( yaw > 0.f )
		{
			rotation[ 1 ] = m_angles[ 1 ] + ( rotation_step[ 1 ] / yaw );
		}
	}

	bool Execute( Camera* camera, BasePlayer* player, BasePlayer* target )
	{
		if( !win32::GetAsyncKeyState( VK_CAPITAL ) )
		{
			return false;
		}

		m_camera = camera;

		if( !memory::IsAddressValid( m_camera ) )
		{
			return false;
		}

		m_player = player;

		if( !memory::IsAddressValid( m_player ) )
		{
			return false;
		}

		auto input = m_player->input();

		if( !memory::IsAddressValid( input ) )
		{
			return false;
		}

		m_item = m_player->GetActiveItem();

		if( !memory::IsAddressValid( m_item ) )
		{
			return false;
		}

		const auto item_info = m_item->info();

		if( memory::IsAddressValid( item_info ) )
		{
			const auto item_name = item_info->shortname();

			if( memory::IsAddressValid( item_name ) )
			{
				auto speed = 250.f;

				switch( constant::Hash( item_name->c_str(), true ) )
				{
					case HASH( L"rifle.bolt" ):
					{
						speed = 656.25f;
						break;
					}
					case HASH( L"rifle.ak" ):
					case HASH( L"rifle.lr300" ):
					case HASH( L"rifle.semiauto" ):
					{
						speed = 375.f;
						break;
					}
					case HASH( L"smg.thompson" ):
					{
						speed = 300.f;
						break;
					}
					case HASH( L"smg.2" ):
					{
						speed = 240.f;
						break;
					}
					case HASH( L"smg.mp5" ):
					{
						speed = 180.f;
						break;
					}
					case HASH( L"pistol.m92" ):
					case HASH( L"pistol.semiauto" ):
					case HASH( L"pistol.python" ):
					{
						speed = 300.f;
						break;
					}
					case HASH( L"crossbow" ):
					{
						speed = 75.f;
						break;
					}
					case HASH( L"bow.hunting" ):
					{
						speed = 50.f;
						break;
					}
					default:
					{
						break;
					}
				}

				auto target_transform = target->get_transform();

				if( memory::IsAddressValid( target_transform ) )
				{
					auto player_transform = m_player->get_transform();
					auto camera_position = camera->get_position();

					// 
					// aim bone - 37 (head)
					// 
					auto position = target->GetBone( 37 );

					Vector3 output = { };
					if( camera->WorldToScreen( position, output ) )
					{
						const auto& io = ImGui::GetIO();
						Vector3 center( io.DisplaySize[ 0 ] * 0.5f, io.DisplaySize[ 1 ] * 0.5f, 0.f );

						const auto fov = center.Distance2D( output );

						if( fov < 15.f )
						{
							auto distance = camera_position.Distance( position );

							if( distance > 0.f )
							{
								auto time = ( distance / speed );
								auto acceleration = target->GetVelocity();

								// 
								// player movement prediction
								// 
								position[ 0 ] += acceleration[ 0 ] * time;
								position[ 2 ] += acceleration[ 2 ] * time;

								constexpr auto gravity = 9.81f;
								const auto drop = 0.5f * gravity * time * time;

								// 
								// bullet drop prediction
								// 
								position[ 1 ] += drop;
							}

							auto direction = camera_position - position;
							auto angles = direction.ToEulerAngles();
							NormalizeAngles( angles );

							if( memory::IsAddressValid( input ) )
							{
								// 
								// rcs
								// 
								const auto recoil = input->recoilAngles();
								angles[ 0 ] -= recoil[ 0 ];
								angles[ 1 ] -= recoil[ 1 ];

								// 
								// smooth
								// 
								// StepConstant( angles );

								input->SetViewVars( angles );
							}
						}
					}
				}
			}
		}

		return true;
	}

protected:
	Camera* m_camera = nullptr;
	BasePlayer* m_player = nullptr;
	Vector3 m_angles = { };
	Item* m_item = nullptr;

	BasePlayer* m_target_player = nullptr;
	float m_target_radius = 0.f;
	float m_target_distance = 0.f;
	Vector3 m_target_position = { };
};

void DumpEntities()
{
	const auto client_entities = BaseNetworkable::clientEntities();

	if( !memory::IsAddressValid( client_entities ) )
	{
		return;
	}

	const auto entity_list = client_entities->entityList();
	
	if( !memory::IsAddressValid( entity_list ) )
	{
		return;
	}

	const auto entities = entity_list->vals;
	
	if( !memory::IsAddressValid( entities ) )
	{
		return;
	}

	if( !memory::IsAddressValid( entities->buffer ) )
	{
		return;
	}

	const auto camera = UnityEngine::Camera::get_main();
	TRACE( "camera = '0x%016llX'", memory::ToAddress( camera ) );

	for( std::int32_t index = 0; index < entities->count; index++ )
	{
		const auto entity = entities->buffer->m_Items[ index ];

		if( memory::IsAddressValid( entity ) )
		{
			const auto transform = entity->get_transform();

			if( memory::IsAddressValid( transform ) )
			{
				const auto position = transform->get_position();

				if( entity->IsA( BasePlayer::StaticClass() ) )
				{
					const auto base_player = static_cast< BasePlayer* >( entity );
					const auto name = base_player->get_displayName();
					const auto health = base_player->get_health();

					if( memory::IsAddressValid( name ) )
					{
						TRACE( L"[%04d] '%s' | '%f' | '%f, %f, %f'", index, name->c_str(), health, position[ 0 ], position[ 1 ], position[ 2 ] );
					}
				}
				else if( entity->IsA( ResourceEntity::StaticClass() ) )
				{
					const auto name = entity->klass->name;
					
					if( memory::IsAddressValid( name ) )
					{
						TRACE( "[%04d] '%s' | '%f, %f, %f'", index, name, position[ 0 ], position[ 1 ], position[ 2 ] );
					}
				}
			}
		}
	}
}

void RenderBones( UnityEngine::Camera* camera, BasePlayer* base_player )
{
	auto& renderer = graphics::Renderer::Instance();

	for( std::size_t index = 0; index < base_player->GetBoneCount(); index++ )
	{
		const auto parent = base_player->GetBoneParent( index );

		if( parent != -1 )
		{
			const auto bone = base_player->GetBone( index );
			const auto bone_parent = base_player->GetBone( parent );

			UnityEngine::Vector3 screen = { };
			UnityEngine::Vector3 screen_parent = { };

			if( camera->WorldToScreen( bone, screen ) && camera->WorldToScreen( bone_parent, screen_parent ) )
			{
				renderer.DrawLine( { screen[ 0 ], screen[ 1 ] }, { screen_parent[ 0 ], screen_parent[ 1 ] }, Color::White() );
			}
		}
	}
}

void Simulate( Camera* camera, BasePlayer* player, Vector3& position )
{
	auto speed = 300.f;

	auto camera_position = camera->get_position();
	// auto position = player->GetBone( 37 );

	auto distance = camera_position.Distance( position );

	if( distance > 0.f )
	{
		auto time = ( distance / speed );
		auto acceleration = player->GetVelocity();

		if( acceleration.Length() > 0.f )
		{
			// TRACE( "acceleration = '%f, %f, %f'", acceleration[ 0 ], acceleration[ 1 ], acceleration[ 2 ] );

			position[ 0 ] += acceleration[ 0 ] * time;
			position[ 1 ] += acceleration[ 1 ] * time;
			position[ 2 ] += acceleration[ 2 ] * time;
		}

		constexpr auto gravity = 9.81f;
		const auto drop = 0.5f * gravity * time * time;

		position[ 1 ] += drop;
	}
}

bool GetBox( UnityEngine::Camera* camera, BasePlayer* base_player, ImVec4& box )
{
	auto& renderer = graphics::Renderer::Instance();

	const auto transform = base_player->get_transform();

	if( !memory::IsAddressValid( transform ) )
	{
		return false;
	}

	const auto model = base_player->playerModel();

	if( !memory::IsAddressValid( model ) )
	{
		return false;
	}

	const auto collision = model->collision();

	if( !memory::IsAddressValid( collision ) )
	{
		return false;
	}

	const auto& bound = base_player->bounds();

	const auto center = bound.m_Center;
	const auto extents = bound.m_Extents;

	const UnityEngine::Vector3 mins =
	{
		-( extents[ 0 ] ),
		-( extents[ 1 ] ),
		-( extents[ 2 ] ),
	};

	const UnityEngine::Vector3 maxs =
	{
		( extents[ 0 ] ),
		( extents[ 1 ] ),
		( extents[ 2 ] ),
	};

	UnityEngine::Vector3 corners[ 8 ] =
	{
		{ mins[ 0 ], mins[ 1 ], mins[ 2 ] },
		{ mins[ 0 ], maxs[ 1 ], mins[ 2 ] },
		{ maxs[ 0 ], maxs[ 1 ], mins[ 2 ] },
		{ maxs[ 0 ], mins[ 1 ], mins[ 2 ] },
		{ maxs[ 0 ], maxs[ 1 ], maxs[ 2 ] },
		{ mins[ 0 ], maxs[ 1 ], maxs[ 2 ] },
		{ mins[ 0 ], mins[ 1 ], maxs[ 2 ] },
		{ maxs[ 0 ], mins[ 1 ], maxs[ 2 ] },
	};

	const auto angles = transform->get_eulerAngles();
	
	auto position = transform->get_position();
	Simulate( camera, base_player, position );

	const auto viewport = renderer.GetViewport();

	box.x = viewport.Width;
	box.y = viewport.Height;
	box.z = -1.f;
	box.w = -1.f;

	const auto yaw = ToRadians( angles[ 1 ] );
	
	const auto sine = -win32::sin( yaw );
	const auto cosine = win32::cos( yaw );

	for( const auto& corner : corners )
	{
		UnityEngine::Vector3 p =
		{
			( position[ 0 ] + center[ 0 ] + ( corner[ 0 ] * cosine - corner[ 2 ] * sine ) ),
			( position[ 1 ] + center[ 1 ] + ( corner[ 1 ] ) ),
			( position[ 2 ] + center[ 2 ] + ( corner[ 0 ] * sine + corner[ 2 ] * cosine ) ),
		};

		UnityEngine::Vector3 screen = { };

		if( !camera->WorldToScreen( p, screen ) )
		{
			return false;
		}

		box.x = std::min( box.x, screen.x );
		box.y = std::min( box.y, screen.y );

		box.z = std::max( box.z, screen.x );
		box.w = std::max( box.w, screen.y );
	}

	return true;
}

void RenderEntities()
{
	auto& aimbot = Aimbot::Instance();
	auto& renderer = graphics::Renderer::Instance();

	const auto client_entities = BaseNetworkable::clientEntities();

	if( !memory::IsAddressValid( client_entities ) )
	{
		return;
	}

	const auto entity_list = client_entities->entityList();

	if( !memory::IsAddressValid( entity_list ) )
	{
		return;
	}

	const auto entities = entity_list->vals;

	if( !memory::IsAddressValid( entities ) )
	{
		return;
	}

	if( !memory::IsAddressValid( entities->buffer ) )
	{
		return;
	}

	const auto camera = UnityEngine::Camera::get_current();

	static BasePlayer* player = nullptr;
	
	for( std::int32_t index = 0; index < entities->count; index++ )
	{
		const auto entity = entities->buffer->m_Items[ index ];

		if( memory::IsAddressValid( entity ) )
		{
			const auto transform = entity->get_transform();

			if( memory::IsAddressValid( transform ) )
			{
				const auto position = transform->get_position();

				UnityEngine::Vector3 screen = { };

				if( camera->WorldToScreen( position, screen ) )
				{
					if( entity->IsA( BasePlayer::StaticClass() ) )
					{
						const auto base_player = static_cast< BasePlayer* >( entity );

						const auto name = base_player->get_displayName();
						const auto health = base_player->get_health();

						if( memory::IsAddressValid( name ) )
						{
							char display[ 256 ] = { };
							win32::sprintf_s( display, sizeof( display ), SECURE( "[%S]" ), name->c_str() );

							if( base_player->IsLocalPlayer() )
							{
								player = base_player;
							}
							else
							{
								if( memory::IsAddressValid( player ) )
								{
									aimbot.Execute( camera, player, base_player );
								}
							}

							RenderBones( camera, base_player );

							ImVec4 box = { };

							if( GetBox( camera, base_player, box ) )
							{
								const auto width = box.z - box.x;
								const auto height = box.w - box.y;

								renderer.DrawBoxBorder( { box.x, box.y }, { width, height }, 1.f, Color::Cyan() );
								renderer.DrawTextShadow( { box.x + width * 0.5f, box.y + height + 2.f }, TextCenterH, Color::Cyan(), display );
								renderer.DrawTextShadow( { box.x + width * 0.5f, box.y + height + 14.f + 2.f }, TextCenterH, Color::White(), SECURE( "[%.2fm]" ), position.Distance( camera->get_position() ) );

								const auto item = base_player->GetActiveItem();

								if( memory::IsAddressValid( item ) )
								{
									const auto info = item->info();

									if( memory::IsAddressValid( info ) )
									{
										const auto item_name = info->shortname();

										if( memory::IsAddressValid( item_name ) )
										{
											std::memset( display, 0, sizeof( display ) );
											win32::sprintf_s( display, sizeof( display ), SECURE( "[%S]" ), item_name->c_str() );
											renderer.DrawTextShadow( { box.x + width * 0.5f, box.y + height + 28.f + 2.f }, TextCenterH, Color::White(), display );
										}
									}
								}
							}
						}
					}
					else if( !entity->IsA( BuildingBlock::StaticClass() ) )
					{
						auto color = Color::White();

						if( entity->IsA( BoxStorage::StaticClass() ) )
						{
							color = Color( 1.f, 0.f, 0.f );
						}
						else if( entity->IsA( GunTrap::StaticClass() ) )
						{
							color = Color( 0.f, 1.f, 1.f );
						}
						else if( entity->IsA( BearTrap::StaticClass() ) )
						{
							color = Color( 1.f, 1.f, 0.f );
						}
						else if( entity->IsA( VendingMachineMapMarker::StaticClass() ) )
						{
							color = Color( 0.f, 0.5f, 0.2f );
						}
						else if( entity->IsA( StashContainer::StaticClass() ) )
						{
							color = Color( 1.f, 0.f, 0.f );
						}
						else if( entity->IsA( BuildingPrivlidge::StaticClass() ) )
						{
							color = Color( 1.f, 0.5f, 0.f );
						}
						else if( entity->IsA( Workbench::StaticClass() ) )
						{
							color = Color( 0.f, 0.05f, 1.f );
						}
						else if( entity->IsA( BaseOven::StaticClass() ) )
						{
							color = Color( 0.5f, 0.f, 1.f );
						}
						else if( entity->IsA( ResearchTable::StaticClass() ) )
						{
							color = Color( 1.f, 0.f, 1.f );
						}
						else if( entity->IsA( DroppedItem::StaticClass() ) )
						{
							color = Color( 1.f, 0.f, 0.f );
						}
						else if( entity->IsA( PlayerCorpse::StaticClass() ) )
						{
							color = Color( 1.f, 1.f, 1.f );
						}
						else if( entity->IsA( OreHotSpot::StaticClass() ) )
						{
							color = Color( 1.f, 0.33f, 1.f );
						}
						else
						{
							continue;
						}

						const auto name = entity->klass->name;

						if( memory::IsAddressValid( name ) )
						{
							renderer.DrawTextShadow( { screen[ 0 ], screen[ 1 ] }, TextLeft, color, SECURE( "[%s]" ), name );
						}
					}
				}
			}
		}
	}
}*/