#pragma once

#include "../../unity/sdk.hpp"

#include "../../unity/object/rust.hpp"
#include "../../unity/object/system.hpp"
#include "../../unity/object/unity_engine.hpp"

namespace rust::features
{

class Visuals : public core::Singleton< Visuals >
{
public:
	void Present();

protected:
	BasePlayer* GetLocalPlayer();

protected:
	bool ComputeBox( BasePlayer* base_player, ImVec4& box );

	void RenderWorld();
	void RenderBaseNetworkable( BaseNetworkable* base_networkable );
	void RenderBasePlayer( BasePlayer* base_player );
	void RenderBoneArray( BasePlayer* base_player, const Color& color );

	void RenderWatermark();

protected:
	using EntityList = System::BufferList< BaseNetworkable* >;
	using EntityArray = System::Array< BaseNetworkable* >;

	EntityList* m_entities = nullptr;
	EntityArray* m_entity_array = nullptr;
	Camera* m_camera = nullptr;	

	BasePlayer* m_player = nullptr;
	int16_t m_player_flags_restore = 0;
	PlayerInput* m_input = nullptr;

	Vector3 m_camera_angles = { };
	Vector3 m_camera_position = { };
};

} // namespace rust::features