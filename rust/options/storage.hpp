#pragma once

#include "../unity/sdk.hpp"

namespace options
{

struct CategoryAimbot
{
	struct
	{
		int m_mode = 2;									// 0 - 2				| 0 - Off, 1 - Auto, 2 - Key
		int m_key = 2;									// 0 - 128			| Aim lock bind
		bool m_auto_fire = false;				//							| Shoot automatically
		bool m_auto_cycle = true;				//							| Change target automatically
	} m_general = { };
	struct
	{
		float m_pitch = 0.f;						// 0 - 100 (%)	| Amount of vertical recoil compensation
		float m_yaw = 0.f;							// 0 - 100 (%)	| Amount of horizontal recoil compensation
	} m_accuracy = { };
	struct
	{
		int m_bone = 37;								// 0 - 128			| Bone to aim at
		int m_priority = 2;							// 0 - 2				| 0 - Random, 1 - Distance, 2 - FOV
		float m_radius = 180.f;					// 0.f - 180.f	| Maximum degrees to target
		float m_distance = 8192.f;			// 0.f - 8192.f	| Maximum distance to target
		bool m_trace = false;						//							| Aim only at visible targets
		bool m_friendly = false;				//							| Aim at friednly targets
	} m_target = { };
	struct
	{
		int m_mode = 0;									// 0 - 2				| 0 - Off, 1 - Constant, 2 - Linear
		float m_pitch = 0.f;						// 0.f - 100.f	| Vertical aim step or smooth amount
		float m_yaw = 0.f;							// 0.f - 100.f	| Horizontal aim step or smooth amount
	} m_step = { };
	struct
	{
		int m_cycle = 0;
		int m_delay = 0;
		int m_duration = 0;
	} m_time = { };
	struct
	{
		bool m_show_fov = false;
	} m_drawings = { };
};

struct CategoryVisuals
{
	bool m_state = true;							//							| Visuals master switch
	int m_box = 1;										// 0 - 2				| 0 - Off, 1 - Normal, 2 - Corners
	bool m_border = true;							//							| Border box black border
	bool m_name = false;							//							| Show player name
	bool m_trace = false;							//							| Show visible players with different color
	bool m_weapon = false;						//							| Show current equipped item
	bool m_skeleton = true;						//							| Show player skeleton
	bool m_distance = true;						//							| Show distance to player

	//other shit
	bool m_show_building_block = false;
	bool m_show_box_storage = false;
	bool m_show_gun_trap = false;
	bool m_show_bear_trap = false;
	bool m_show_vending = false;
	bool m_show_stash_container = false;
	bool m_show_building_privledge = false;
	bool m_show_workbench = false;
	bool m_show_base_oven = false;
	bool m_show_research_table = false;
	bool m_show_dropped_item = false;
	bool m_show_player_corpse = false;
	bool m_show_ore_hot_spot = false;
};

struct CategoryCommon
{
	bool m_crosshair = true;					//							| Show crosshair in screen center

	//bool m_debug_time = false;				//							| Always day                 } its a shit, need one option. 'admin mode'
	//bool m_debug_camera = false;			//							| Admin debug camera         } its a shit, need one option. 'admin mode'
	bool m_admin_mode = false;
};

struct CategoryColors
{
	struct
	{
		Color m_box = Color::Cyan();
		Color m_border = Color::Black();
		Color m_name = Color::White();
		Color m_trace = Color::Green();
		Color m_weapon = Color::White();
		Color m_skeleton = Color::White();
		Color m_skeleton_invisible = Color::Red();
		Color m_distance = Color::White();
		Color m_box_storage = Color(1.f, 0.f, 0.f);
		Color m_gun_trap = Color(0.f, 1.f, 1.f);
		Color m_bear_trap = Color(1.f, 1.f, 0.f);
		Color m_vedning = Color(0.f, 0.5f, 0.2f);
		Color m_stash_container = Color(1.f, 0.f, 0.f);
		Color m_building_privledge = Color(1.f, 0.5f, 0.f);
		Color m_workbench = Color(0.f, 0.05f, 1.f);
		Color m_base_oven = Color(0.5f, 0.f, 1.f);
		Color m_research_table = Color(1.f, 0.f, 1.f);
		Color m_dropped_item = Color(1.f, 0.f, 0.f);
		Color m_player_corpse = Color(1.f, 1.f, 1.f);
		Color m_ore_hot_spot = Color(1.f, 0.33f, 1.f);

	} m_visuals = { };
	struct
	{
		Color m_crosshair = Color::Cyan();
	} m_common = { };
};

extern CategoryAimbot m_aimbot;
extern CategoryVisuals m_visuals;
extern CategoryCommon m_common;
extern CategoryColors m_colors;

bool Load( const std::wstring& name );
bool Save( const std::wstring& name );

} // namespace options