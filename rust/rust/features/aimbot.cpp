#include "aimbot.hpp"

#include "../../options/storage.hpp"

float DirectionToRadius( const Vector3& angles, const Vector3& begin, const Vector3& end )
{
	auto direction = ( end - begin );
	direction.Normalize();

	auto forward = angles.ToVector();
	forward.Normalize();

	const auto dot = std::clamp( forward.Dot( direction ), -1.f, 1.f );
	return UnityEngine::ToDegrees( win32::acos( dot ) );
}

namespace rust::features
{

void Aimbot::Execute( BasePlayer* player )
{
	const auto& general = options::m_aimbot.m_general;
	const auto& accuracy = options::m_aimbot.m_accuracy;
	const auto& step = options::m_aimbot.m_step;
	const auto& time = options::m_aimbot.m_time;

	if( !general.m_mode )
	{
		return;
	}

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

	m_player = player;

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

	if( general.m_mode == 2 )
	{
		if( !win32::GetAsyncKeyState( general.m_key ) )
		{
			m_target_cycle = true;
			m_target_timer.reset();
			return;
		}
	}

	if( m_target_cycle )
	{
		TargetUpdate();
	}

	if( TargetValidate( m_target_index ) )
	{
		if( time.m_delay )
		{
			if( m_target_timer.elapsed() < time.m_delay )
			{
				// 
				// delay before locking
				// 
				return;
			}
		}

		if( time.m_duration )
		{
			if( m_target_timer.elapsed() >= time.m_duration )
			{
				// 
				// release lock
				// 
				return;
			}
		}

		auto direction = ( m_target_position - m_camera_position );
		direction.Normalize();

		auto angles = direction.ToEulerAngles();
		UnityEngine::AnglesNormalize( angles );

		const auto& angles_recoil = m_input->recoilAngles();

		if( accuracy.m_pitch > 0.f )
		{
			angles[ 0 ] -= ( angles_recoil[ 0 ] * ( accuracy.m_pitch / 100.f ) );
		}

		if( accuracy.m_yaw > 0.f )
		{
			angles[ 1 ] -= ( angles_recoil[ 1 ] * ( accuracy.m_yaw / 100.f ) );
		}

		if( step.m_mode == 1 )
		{
			StepConstant( angles );
		}
		else if( step.m_mode == 2 )
		{
			StepDecreasing( angles );
		}

		UnityEngine::AnglesNormalize( angles );

		m_input->SetViewVars( angles );

		if( general.m_auto_fire )
		{

		}
	}
	else
	{
		if( general.m_auto_cycle )
		{
			if( time.m_cycle )
			{
				if( m_target_timer.elapsed() < time.m_cycle )
				{
					// 
					// delay before target update
					// 
					return;
				}
			}

			m_target_cycle = true;
		}
	}
}

bool Aimbot::TargetValidate( std::int32_t index )
{
	const auto& general = options::m_aimbot.m_general;
	const auto& target = options::m_aimbot.m_target;

	if( index < 0 || index >= m_entities->count )
	{
		return false;
	}

	const auto base_networkable = m_entity_array->m_Items[ index ];

	if( !memory::IsAddressValid( base_networkable ) )
	{
		return false;
	}

	if( !base_networkable->IsA( BasePlayer::StaticClass() ) )
	{
		return false;
	}

	const auto base_player = static_cast< BasePlayer* >( base_networkable );

	if( base_player->IsLocalPlayer() )
	{
		return false;
	}

	auto position = base_player->GetBone(target.m_bone);

	if (position.IsZero())
	{
		return false;
	}

	if (!UnityEngine::Physics::Raycast(m_camera_position, position))
	{
		return false;
	}

	TargetSimulate( base_player, position );

	const auto distance = m_camera_position.Distance( position );

	if( distance > target.m_distance )
	{
		return false;
	}

	m_target_distance = distance;

	const auto radius = DirectionToRadius( m_camera_angles, m_camera_position, position );

	if( radius >= target.m_radius )
	{
		return false;
	}

	m_target_radius = radius;
	m_target_position = position;

	return true;
}

void Aimbot::TargetUpdate()
{
	const auto& general = options::m_aimbot.m_general;
	const auto& target = options::m_aimbot.m_target;

	auto best_distance = std::numeric_limits< float >::max();

	if( target.m_priority == 1 )
	{
		// 
		// sort by distance
		// 
		best_distance = target.m_distance;
	}
	else if( target.m_priority == 2 )
	{
		// 
		// sort by radius
		// 
		best_distance = target.m_radius;
	}

	for( std::int32_t index = 0; index < m_entities->count; index++ )
	{
		if( TargetValidate( index ) )
		{
			if( target.m_priority == 0 )
			{
				// 
				// use any target
				// 
				m_target_cycle = false;
				m_target_index = index;
				break;
			}
			else if( target.m_priority == 1 )
			{
				// 
				// use nearest target
				// 
				if( m_target_distance < best_distance )
				{
					best_distance = m_target_distance;
					m_target_cycle = false;
					m_target_index = index;
				}
			}
			else if( target.m_priority == 2 )
			{
				// 
				// use target closest to crosshair
				// 
				if( m_target_radius < best_distance )
				{
					best_distance = m_target_radius;
					m_target_cycle = false;
					m_target_index = index;
				}
			}
		}
	}
}

void Aimbot::TargetSimulate( BasePlayer* base_player, Vector3& position )
{
	auto item = m_player->GetActiveItem();

	if( !memory::IsAddressValid( item ) )
	{
		return;
	}

	auto item_info = item->info();

	if( !memory::IsAddressValid( item_info ) )
	{
		return;
	}

	auto item_name = item_info->shortname();

	if( !memory::IsAddressValid( item_name ) )
	{
		return;
	}

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
			speed = 55.f;
			break;
		}
		default:
		{
			break;
		}
	}

	auto distance = m_camera_position.Distance( position );

	if( distance > 0.f )
	{
		auto time = ( distance / speed );
		auto velocity = base_player->GetVelocity();

		position[ 0 ] += velocity[ 0 ] * time;
		position[ 1 ] += velocity[ 1 ] * time;
		position[ 2 ] += velocity[ 2 ] * time;

		constexpr auto gravity = 9.81f;
		const auto drop = 0.5f * gravity * time * time;

		position[ 1 ] += drop;
	}
}

std::int32_t Aimbot::GetTargetIndex() const
{
	return m_target_index;
}

void Aimbot::StepConstant( Vector3& angles )
{
	const auto& step = options::m_aimbot.m_step;

	auto angles_step = ( angles - m_camera_angles );
	UnityEngine::AnglesNormalize( angles_step );

	if( step.m_pitch > 0.f )
	{
		auto factor_pitch = ( step.m_pitch / 100.f );

		if( angles_step[ 0 ] < 0.f )
		{
			if( factor_pitch > std::abs( angles_step[ 0 ] ) )
			{
				factor_pitch = std::abs( angles_step[ 0 ] );
			}

			angles[ 0 ] = m_camera_angles[ 0 ] - factor_pitch;
		}
		else
		{
			if( factor_pitch > angles_step[ 0 ] )
			{
				factor_pitch = angles_step[ 0 ];
			}

			angles[ 0 ] = m_camera_angles[ 0 ] + factor_pitch;
		}
	}

	if( step.m_yaw > 0.f )
	{
		auto factor_yaw = ( step.m_yaw / 100.f );

		if( angles_step[ 1 ] < 0.f )
		{
			if( factor_yaw > std::abs( angles_step[ 1 ] ) )
			{
				factor_yaw = std::abs( angles_step[ 1 ] );
			}

			angles[ 1 ] = m_camera_angles[ 1 ] - factor_yaw;
		}
		else
		{
			if( factor_yaw > angles_step[ 1 ] )
			{
				factor_yaw = angles_step[ 1 ];
			}

			angles[ 1 ] = m_camera_angles[ 1 ] + factor_yaw;
		}
	}
}

void Aimbot::StepDecreasing( Vector3& angles )
{
	const auto& step = options::m_aimbot.m_step;

	auto angles_step = ( angles - m_camera_angles );
	UnityEngine::AnglesNormalize( angles_step );

	if( step.m_pitch > 0.f )
	{
		angles[ 0 ] = m_camera_angles[ 0 ] + ( angles_step[ 0 ] / step.m_pitch );
	}

	if( step.m_yaw > 0.f )
	{
		angles[ 1 ] = m_camera_angles[ 1 ] + ( angles_step[ 1 ] / step.m_yaw );
	}
}

} // namespace rust::features