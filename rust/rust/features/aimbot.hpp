#pragma once

#include "../../unity/sdk.hpp"

#include "../../unity/object/rust.hpp"
#include "../../unity/object/system.hpp"
#include "../../unity/object/unity_engine.hpp"

namespace rust::features
{

class Aimbot : public core::Singleton< Aimbot >
{
public:
	void Execute( BasePlayer* player );

public:
	bool TargetValidate( std::int32_t index );
	void TargetUpdate();
	void TargetSimulate( BasePlayer* base_player, Vector3& position );

	std::int32_t GetTargetIndex() const;

protected:
	void StepConstant( Vector3& angles );
	void StepDecreasing( Vector3& angles );

protected:
	using EntityList = System::BufferList< BaseNetworkable* >;
	using EntityArray = System::Array< BaseNetworkable* >;

protected:
	EntityList* m_entities = nullptr;
	EntityArray* m_entity_array = nullptr;
	Camera* m_camera = nullptr;

	BasePlayer* m_player = nullptr;
	PlayerInput* m_input = nullptr;

	Vector3 m_camera_angles = { };
	Vector3 m_camera_position = { };

	bool m_target_cycle = true;
	std::int32_t m_target_index = -1;
	Vector3 m_target_position = { };
	float m_target_radius = 0.f;
	float m_target_distance = 0.f;
	core::Timer m_target_timer = { };
	BasePlayer* m_target_player = nullptr;
};

} // namespace rust::features