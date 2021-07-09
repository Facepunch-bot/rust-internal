#include "visuals.hpp"
#include "aimbot.hpp"
#include "user_interface.hpp"

#include "../core.hpp"
#include "../il2cpp.hpp"

#include "../../options/storage.hpp"

float DirectionToRadius( const Vector3& angles, const Vector3& begin, const Vector3& end );

namespace rust::features
{

void Visuals::Present()
{
	RenderWorld();
	RenderWatermark();
}

BasePlayer* Visuals::GetLocalPlayer()
{
	for( std::int32_t index = 0; index < m_entities->count; index++ )
	{
		auto base_networkable = m_entity_array->m_Items[ index ];

		if( memory::IsAddressValid( base_networkable ) )
		{
			if( base_networkable->IsA( BasePlayer::StaticClass() ) )
			{
				auto base_player = static_cast< BasePlayer* >( base_networkable );

				if( base_player->IsLocalPlayer() )
				{
					return base_player;
				}
			}
		}
	}

	return nullptr;
}

bool Visuals::ComputeBox( BasePlayer* base_player, ImVec4& box )
{
	const auto& io = ImGui::GetIO();

	const auto transform = base_player->get_transform();

	if( !memory::IsAddressValid( transform ) )
	{
		return false;
	}

	const auto& bounds = base_player->bounds();

	const auto center = bounds.m_Center;
	const auto extents = bounds.m_Extents;

	const auto mins = -extents;
	const auto maxs = extents;

	Vector3 corners[ 8 ] =
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

	const auto position = transform->get_position();
	const auto angles = transform->get_eulerAngles();

	box.x = io.DisplaySize[ 0 ];
	box.y = io.DisplaySize[ 1 ];
	box.z = -1.f;
	box.w = -1.f;

	const auto yaw = UnityEngine::ToRadians( angles[ 1 ] );

	const auto sine = -win32::sin( yaw );
	const auto cosine = win32::cos( yaw );

	for( const auto& corner : corners )
	{
		Vector3 world =
		{
			( position[ 0 ] + center[ 0 ] + ( corner[ 0 ] * cosine - corner[ 2 ] * sine ) ),
			( position[ 1 ] + center[ 1 ] + ( corner[ 1 ] ) ),
			( position[ 2 ] + center[ 2 ] + ( corner[ 0 ] * sine + corner[ 2 ] * cosine ) ),
		};

		Vector3 screen = { };

		if( UnityEngine::WorldToScreen( world, screen ) )
		{
			box.x = std::min( box.x, screen.x );
			box.y = std::min( box.y, screen.y );
			box.z = std::max( box.z, screen.x );
			box.w = std::max( box.w, screen.y );
		}
	}

	return true;
}

void Visuals::RenderWorld()
{
	auto& aimbot = Aimbot::Instance();

	auto client_entities = BaseNetworkable::clientEntities();

	if( !memory::IsAddressValid( client_entities ) )
	{
		return;
	}

	auto entities = client_entities->entityList();

	if( !memory::IsAddressValid( entities ) )
	{
		return;
	}

	m_entities = entities->vals;

	if( !memory::IsAddressValid( m_entities ) )
	{
		return;
	}

	m_entity_array = m_entities->buffer;

	if( !memory::IsAddressValid( m_entity_array ) )
	{
		return;
	}

	m_camera = Camera::get_current();

	if( !memory::IsAddressValid( m_camera ) )
	{
		return;
	}
	
	m_player = GetLocalPlayer();
	
	if( !memory::IsAddressValid( m_player ) )
	{
		return;
	}

	m_input = m_player->input();

	if( !memory::IsAddressValid( m_input ) )
	{
		return;
	}

	m_camera_angles = m_input->bodyAngles();
	m_camera_position = m_camera->get_position();

	aimbot.Execute( m_player );

	auto& visuals = options::m_visuals;

	if( !visuals.m_state )
	{
		return;
	}

	for( std::int32_t index = 0; index < m_entities->count; index++ )
	{
		auto base_networkable = m_entity_array->m_Items[ index ];

		if( memory::IsAddressValid( base_networkable ) )
		{
			RenderBaseNetworkable( base_networkable );
		}
	}

	if (options::m_aimbot.m_drawings.m_show_fov)
	{
		if(memory::IsAddressValid(m_camera))
		{
			auto& renderer = graphics::Renderer::Instance();
			const auto& viewport = renderer.GetViewport();

			auto fov = m_camera->get_fieldOfView();
			auto fov_scale = 1.f;
			
			const auto fov_aimbot = win32::tan(UnityEngine::ToRadians(options::m_aimbot.m_target.m_radius * fov_scale) / 2.f);
			const auto fov_view = win32::tan(UnityEngine::ToRadians(fov) / 2.f);

			const auto fov_radius = (fov_aimbot / fov_view) * viewport.Width;

			// 
			// show aimbot fov
			// 
			renderer.DrawCircle({ viewport.Width * 0.5f, viewport.Height * 0.5f }, fov_radius, Color::White(), 64);
		}
	}

	if (options::m_common.m_admin_mode)
	{
		//if (!m_player->IsAdminGetterHooked())
		//{
		//	if (!m_player->HookIsAdminGetter())
		//	{
		//		m_player->playerFlags() |= 4;
		//	}
		//}
		//else
		//{
		//	m_player->playerFlags() |= 4;
		//}

		m_player_flags_restore = m_player->playerFlags();
		m_player->playerFlags() |= 4;
	}
	else
	{
		m_player->playerFlags() = m_player_flags_restore;

		//if (m_player->IsAdminGetterHooked())
		//{
		//	if (!m_player->UnhookIsAdminGetter())
		//	{
		//		m_player->playerFlags() = m_player->m_restore_player_flags;
		//	}
		//}
		//else
		//{
		//	m_player->playerFlags() = m_player->m_restore_player_flags;
		//}
	}
}

void Visuals::RenderBaseNetworkable( BaseNetworkable* base_networkable )
{
	auto& renderer = graphics::Renderer::Instance();
	const auto& visuals = options::m_visuals;

	if( base_networkable->IsA( BasePlayer::StaticClass() ) )
	{
		auto base_player = static_cast< BasePlayer* >( base_networkable );
		if ((base_player->IsA(BaseNpc::StaticClass())) || (base_player->wasSleeping()))
		{
			/* 
			* skip sleepers & npc's
			*/
			return;
		}

		RenderBasePlayer( base_player );
	}
	else
	{
		const auto& ui = UserInterface::Instance();
		if (!ui.m_panic_enabled)
		{
			if (!base_networkable->IsA(BuildingBlock::StaticClass()))
			{
				auto color = Color::White();

				if (base_networkable->IsA(BoxStorage::StaticClass()) && visuals.m_show_box_storage)
				{
					color = options::m_colors.m_visuals.m_box_storage;
				}
				else if (base_networkable->IsA(GunTrap::StaticClass()) && visuals.m_show_gun_trap)
				{
					color = options::m_colors.m_visuals.m_gun_trap;
				}
				else if (base_networkable->IsA(BearTrap::StaticClass()) && visuals.m_show_bear_trap)
				{
					color = options::m_colors.m_visuals.m_bear_trap;
				}
				else if (base_networkable->IsA(VendingMachineMapMarker::StaticClass()) && visuals.m_show_vending)
				{
					color = options::m_colors.m_visuals.m_vedning;
				}
				else if (base_networkable->IsA(StashContainer::StaticClass()) && visuals.m_show_stash_container)
				{
					color = options::m_colors.m_visuals.m_stash_container;
				}
				else if (base_networkable->IsA(BuildingPrivlidge::StaticClass()) && visuals.m_show_building_privledge)
				{
					color = options::m_colors.m_visuals.m_building_privledge;
				}
				else if (base_networkable->IsA(Workbench::StaticClass()) && visuals.m_show_workbench)
				{
					color = options::m_colors.m_visuals.m_workbench;
				}
				else if (base_networkable->IsA(BaseOven::StaticClass()) && visuals.m_show_base_oven)
				{
					color = options::m_colors.m_visuals.m_base_oven;
				}
				else if (base_networkable->IsA(ResearchTable::StaticClass()) && visuals.m_show_research_table)
				{
					color = options::m_colors.m_visuals.m_research_table;
				}
				else if (base_networkable->IsA(DroppedItem::StaticClass()) && visuals.m_show_dropped_item)
				{
					color = options::m_colors.m_visuals.m_dropped_item;
				}
				else if (base_networkable->IsA(PlayerCorpse::StaticClass()) && visuals.m_show_player_corpse)
				{
					color = options::m_colors.m_visuals.m_player_corpse;
				}
				else if (base_networkable->IsA(OreHotSpot::StaticClass()) && visuals.m_show_ore_hot_spot)
				{
					color = options::m_colors.m_visuals.m_ore_hot_spot;
				}
				else
				{
					// quit from method if object is thelupa
					return;
				}

				const auto name = base_networkable->klass->name;

				if (memory::IsAddressValid(name))
				{
					Vector3 screen = { };

					if (UnityEngine::WorldToScreen(base_networkable->get_position(), screen))
					{
						renderer.DrawTextShadow({ screen[0], screen[1] }, TextLeft, color, SECURE("[%s]"), name);
					}
				}
			}
		}
		else
		{
			renderer.DrawTextShadow({ 10.f, 10.f }, TextCenterV, Color::Red(), SECURE("panic mode"));
		}
	}
}

void Visuals::RenderBasePlayer( BasePlayer* base_player )
{
	auto& renderer = graphics::Renderer::Instance();
	auto& visuals = options::m_visuals;
	auto& colors = options::m_colors.m_visuals;
	const auto position = base_player->get_position();

	if( base_player->IsLocalPlayer() )
	{
		// 
		// skip local player
		// 
		return;
	}

	if (base_player->get_health() <= 0.f)
	{
		/*
		* Skip if died
		*/
		return;
	}

	if( visuals.m_skeleton )
	{
		// 
		// draw player skeleton
		// 

		if (!UnityEngine::Physics::Raycast(m_camera_position, position))
		{
			RenderBoneArray(base_player, colors.m_skeleton_invisible);
		}
		else
		{
			RenderBoneArray(base_player, colors.m_skeleton);
		}
	}

	ImVec4 box = { };

	if( ComputeBox( base_player, box ) )
	{
		const ImVec2 screen( box.x, box.y );

		const auto width = box.z - box.x;
		const auto height = box.w - box.y;

		if( visuals.m_box == 1 )
		{
			if( visuals.m_border )
			{
				renderer.DrawBoxBorder( screen, { width, height }, 1.f, colors.m_box, colors.m_border );
			}
			else
			{
				renderer.DrawBox( screen, { width, height }, 1.f, colors.m_box );
			}
		}
		else if( visuals.m_box == 2 )
		{
			if( visuals.m_border )
			{
				renderer.DrawCornerBoxBorder( screen, { width, height }, 1.f, colors.m_box, colors.m_border );
			}
			else
			{
				renderer.DrawCornerBox( screen, { width, height }, 1.f, colors.m_box );
			}
		}

		ImVec2 render_pad( 0.f, 0.f );

		if( visuals.m_name )
		{
			const auto name = base_player->get_displayName();

			if( memory::IsAddressValid( name ) )
			{
				char display[ 256 ] = { };
				ImTextStrToUtf8( display, ARRAYSIZE( display ), ( const ImWchar* )name->begin(), ( const ImWchar* )name->end() );

				const auto size = ImGui::CalcTextSize( display );
				renderer.DrawTextShadow( { screen[ 0 ] + ( width * 0.5f ), screen[ 1 ] + height + render_pad[ 1 ] + 2.f }, TextCenterH, colors.m_name, display );
				render_pad[ 1 ] += size[ 1 ];
			}
		}

		if( visuals.m_weapon )
		{
			const auto item = base_player->GetActiveItem();

			if( memory::IsAddressValid( item ) )
			{
				const auto item_info = item->info();

				if( memory::IsAddressValid( item_info ) )
				{
					const auto name = item_info->shortname();

					if( memory::IsAddressValid( name ) )
					{
						char display[ 256 ] = { };
						ImTextStrToUtf8( display, ARRAYSIZE( display ), ( const ImWchar* )name->begin(), ( const ImWchar* )name->end() );

						const auto size = ImGui::CalcTextSize( display );
						renderer.DrawTextShadow( { screen[ 0 ] + ( width * 0.5f ), screen[ 1 ] + height + render_pad[ 1 ] + 2.f }, TextCenterH, colors.m_name, display );
						render_pad[ 1 ] += size[ 1 ];
					}
				}
			}
		}

		if( visuals.m_distance )
		{
			const auto distance = m_camera_position.Distance( base_player->get_position() );
			
			char display[ 256 ] = { };
			win32::sprintf_s( display, ARRAYSIZE( display ), SECURE( "[%.2fm]" ), distance );

			const auto size = ImGui::CalcTextSize( display );
			renderer.DrawTextShadow( { screen[ 0 ] + ( width * 0.5f ), screen[ 1 ] + height + render_pad[ 1 ] + 2.f }, TextCenterH, colors.m_distance, display );
			render_pad[ 1 ] += size[ 1 ];
		}
	}
}

void Visuals::RenderBoneArray( BasePlayer* base_player, const Color& color )
{
	auto& renderer = graphics::Renderer::Instance();
	
	for( std::size_t index = 0; index < base_player->GetBoneCount(); index++ )
	{
		const auto parent = base_player->GetBoneParent( index );

		if( parent != -1 )
		{
			const auto bone = base_player->GetBone( index );
			const auto bone_parent = base_player->GetBone( parent );

			Vector3 screen = { };
			Vector3 screen_parent = { };

			if( UnityEngine::WorldToScreen( bone, screen ) &&
					UnityEngine::WorldToScreen( bone_parent, screen_parent ) )
			{
				renderer.DrawLine( { screen[ 0 ], screen[ 1 ] }, { screen_parent[ 0 ], screen_parent[ 1 ] }, color );
			}
		}
	}
}

void Visuals::RenderWatermark()
{
	auto& renderer = graphics::Renderer::Instance();
	const auto& common = options::m_common;
	const auto& colors = options::m_colors.m_common;

	if( common.m_crosshair )
	{
		const auto& io = ImGui::GetIO();
		const ImVec2 center( io.DisplaySize[ 0 ] * 0.5f, io.DisplaySize[ 1 ] * 0.5f );

		renderer.DrawLine( { center[ 0 ] - 10.f, center[ 1 ] }, { center[ 0 ] + 10.f, center[ 1 ] }, colors.m_crosshair );
		renderer.DrawLine( { center[ 0 ], center[ 1 ] - 10.f }, { center[ 0 ], center[ 1 ] + 10.f }, colors.m_crosshair );
	}

	// renderer.DrawTextShadow( { 10.f, 10.f + 16.f }, TextLeft, Color::White(), SECURE( "%f, %f" ), m_camera_angles[ 0 ], m_camera_angles[ 1 ] );
}

} // namespace rust::features