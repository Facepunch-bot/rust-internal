#include "user_interface.hpp"
#include "../../options/storage.hpp"

namespace ImGui
{

bool g_key_waiting = false;
int* g_key_output = nullptr;

int TranslateMouseButton( ImGuiMouseButton button )
{
	switch( button )
	{
		case ImGuiMouseButton_Left:
		{
			return 1;
		}
		case ImGuiMouseButton_Right:
		{
			return 2;
		}
		case ImGuiMouseButton_Middle:
		{
			return 4;
		}
		case 3:
		{
			return 5;
		}
		case 4:
		{
			return 6;
		}
	}

	return 0;
}

void KeyBind( const char* label, int* key )
{
	if( !key )
	{
		return;
	}

	if( g_key_waiting )
	{
		for( auto index = 0; index < ImGuiMouseButton_COUNT; index++ )
		{
			if( ImGui::IsMouseReleased( index ) )
			{
				( *key ) = TranslateMouseButton( index );
				g_key_output = key;
				g_key_waiting = false;
				break;
			}
		}

		for( auto index = 0; index < 512; index++ )
		{
			if( ImGui::IsKeyReleased( index ) )
			{
				( *key ) = index;
				g_key_output = key;
				g_key_waiting = false;
				break;
			}
		}
	}

	auto key_code = g_map_data.NtUserMapVirtualKeyEx( *key, MAPVK_VK_TO_VSC_EX, 0, 0 );

	switch( *key )
	{
		case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
		case VK_RCONTROL: case VK_RMENU:
		case VK_LWIN: case VK_RWIN: case VK_APPS:
		case VK_PRIOR: case VK_NEXT:
		case VK_END: case VK_HOME:
		case VK_INSERT: case VK_DELETE:
		case VK_DIVIDE:
		case VK_NUMLOCK:
		{
			key_code |= KF_EXTENDED;
			break;
		}
	}

	wchar_t wide_key_name[ 128 ] = { };
	g_map_data.NtUserGetKeyNameText( key_code << 16, wide_key_name, ARRAYSIZE( wide_key_name ) );

	char key_name[ 128 ] = { };
	win32::sprintf_s( key_name, ARRAYSIZE( key_name ), SECURE( "[%u] %ws" ), *key, wide_key_name );

	const char* text = nullptr;

	if( g_key_waiting && g_key_output == key )
	{
		text = "...";
	}
	else
	{
		text = key_name;
	}

	if( ImGui::Button( text, { -1.f, 0.f } ) )
	{
		g_key_output = key;
		g_key_waiting = true;
	}
}

} // namespace ImGui

namespace ImGui
{

void StyleColorsAtom( ImGuiStyle* dst = nullptr )
{
	auto style = dst ? dst : &ImGui::GetStyle();
	auto colors = style->Colors;

	style->WindowPadding = { 4.f, 4.f };
	style->FramePadding = { 4.f, 2.f };
	style->ItemSpacing = { 4.f, 4.f };
	style->ItemInnerSpacing = { 4.f, 4.f };
	style->TouchExtraPadding = { 0.f, 0.f };
	style->IndentSpacing = 30.f;
	style->ScrollbarSize = 10.f;
	style->GrabMinSize = 6.f;

	style->WindowBorderSize = 0.f;
	style->ChildBorderSize = 1.f;
	style->PopupBorderSize = 1.f;
	style->FrameBorderSize = 1.f;
	style->TabBorderSize = 1.f;

	style->WindowRounding = 0.f;
	style->ChildRounding = 0.f;
	style->FrameRounding = 0.f;
	style->PopupRounding = 0.f;
	style->ScrollbarRounding = 0.f;
	style->GrabRounding = 0.f;
	style->TabRounding = 0.f;

	colors[ ImGuiCol_Text ] = { 0.86f, 0.86f, 0.86f, 1.00f };
	colors[ ImGuiCol_TextDisabled ] = { 0.43f, 0.43f, 0.43f, 1.00f };
	colors[ ImGuiCol_WindowBg ] = { 0.16f, 0.16f, 0.16f, 1.00f };
	colors[ ImGuiCol_ChildBg ] = { 0.00f, 0.00f, 0.00f, 0.00f };
	colors[ ImGuiCol_PopupBg ] = { 0.08f, 0.08f, 0.08f, 0.94f };
	colors[ ImGuiCol_Border ] = { 0.31f, 0.31f, 0.31f, 1.00f };
	colors[ ImGuiCol_BorderShadow ] = { 0.00f, 0.00f, 0.00f, 0.00f };
	colors[ ImGuiCol_FrameBg ] = { 0.12f, 0.12f, 0.12f, 1.00f };
	colors[ ImGuiCol_FrameBgHovered ] = { 0.13f, 0.13f, 0.13f, 1.00f };
	colors[ ImGuiCol_FrameBgActive ] = { 0.15f, 0.15f, 0.15f, 1.00f };
	colors[ ImGuiCol_TitleBg ] = { 0.08f, 0.08f, 0.08f, 1.00f };
	colors[ ImGuiCol_TitleBgActive ] = { 0.09f, 0.09f, 0.09f, 1.00f };
	colors[ ImGuiCol_TitleBgCollapsed ] = { 0.11f, 0.11f, 0.11f, 1.00f };
	colors[ ImGuiCol_MenuBarBg ] = { 0.12f, 0.12f, 0.12f, 1.00f };
	colors[ ImGuiCol_ScrollbarBg ] = { 0.12f, 0.12f, 0.12f, 1.00f };
	colors[ ImGuiCol_ScrollbarGrab ] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ ImGuiCol_ScrollbarGrabHovered ] = { 0.78f, 0.41f, 0.41f, 1.00f };
	colors[ ImGuiCol_ScrollbarGrabActive ] = { 0.82f, 0.45f, 0.45f, 1.00f };
	colors[ ImGuiCol_CheckMark ] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ ImGuiCol_SliderGrab ] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ ImGuiCol_SliderGrabActive ] = { 0.82f, 0.45f, 0.45f, 1.00f };
	colors[ ImGuiCol_Button ] = { 0.14f, 0.14f, 0.14f, 1.00f };
	colors[ ImGuiCol_ButtonHovered ] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ ImGuiCol_ButtonActive ] = { 0.78f, 0.41f, 0.41f, 1.00f };
	colors[ ImGuiCol_Header ] = { 0.14f, 0.14f, 0.14f, 1.00f };
	colors[ ImGuiCol_HeaderHovered ] = { 0.75f, 0.37f, 0.37f, 1.00f };
	colors[ ImGuiCol_HeaderActive ] = { 0.78f, 0.41f, 0.41f, 1.00f };
	colors[ ImGuiCol_Separator ] = { 0.43f, 0.43f, 0.50f, 0.50f };
	colors[ ImGuiCol_SeparatorHovered ] = { 0.10f, 0.40f, 0.75f, 0.78f };
	colors[ ImGuiCol_SeparatorActive ] = { 0.10f, 0.40f, 0.75f, 1.00f };
	colors[ ImGuiCol_ResizeGrip ] = { 0.26f, 0.59f, 0.98f, 0.25f };
	colors[ ImGuiCol_ResizeGripHovered ] = { 0.26f, 0.59f, 0.98f, 0.67f };
	colors[ ImGuiCol_ResizeGripActive ] = { 0.26f, 0.59f, 0.98f, 0.95f };
	colors[ ImGuiCol_Tab ] = { 0.18f, 0.35f, 0.58f, 0.86f };
	colors[ ImGuiCol_TabHovered ] = { 0.26f, 0.59f, 0.98f, 0.80f };
	colors[ ImGuiCol_TabActive ] = { 0.20f, 0.41f, 0.68f, 1.00f };
	colors[ ImGuiCol_TabUnfocused ] = { 0.07f, 0.10f, 0.15f, 0.97f };
	colors[ ImGuiCol_TabUnfocusedActive ] = { 0.14f, 0.26f, 0.42f, 1.00f };
	colors[ ImGuiCol_PlotLines ] = { 0.61f, 0.61f, 0.61f, 1.00f };
	colors[ ImGuiCol_PlotLinesHovered ] = { 1.00f, 0.43f, 0.35f, 1.00f };
	colors[ ImGuiCol_PlotHistogram ] = { 0.90f, 0.70f, 0.00f, 1.00f };
	colors[ ImGuiCol_PlotHistogramHovered ] = { 1.00f, 0.60f, 0.00f, 1.00f };
	colors[ ImGuiCol_TextSelectedBg ] = { 0.78f, 0.41f, 0.41f, 1.00f };
	colors[ ImGuiCol_DragDropTarget ] = { 1.00f, 1.00f, 0.00f, 0.90f };
	colors[ ImGuiCol_NavHighlight ] = { 0.26f, 0.59f, 0.98f, 1.00f };
	colors[ ImGuiCol_NavWindowingHighlight ] = { 1.00f, 1.00f, 1.00f, 0.70f };
	colors[ ImGuiCol_NavWindowingDimBg ] = { 0.80f, 0.80f, 0.80f, 0.20f };
	colors[ ImGuiCol_ModalWindowDimBg ] = { 0.80f, 0.80f, 0.80f, 0.35f };
}

bool Items_VectorGetter( void* data, int n, const char** out_text )
{
	const auto& v = *static_cast< const std::vector< std::string >* >( data );
	*out_text = v[ n ].c_str();
	return true;
}

bool Combo( const char* label, int* current_item, std::vector< std::string >& items, int popup_max_height_in_items = -1 )
{
	return ImGui::Combo( label, current_item, Items_VectorGetter,
											 &items, static_cast< int >( items.size() ),
											 popup_max_height_in_items );
}

} // namespace ImGui

namespace rust::features
{

UserInterface::~UserInterface()
{
	Destroy();
}

bool UserInterface::Create()
{
	auto& input_manager = win32::InputManager::Instance();

	if( !input_manager.RegisterEvent( HASH( L"UserInterface::MessageEvent" ), &MessageEvent ) )
	{
		TRACE( "%s: InputManager::RegisterEvent( ... ) error!", ATOM_FUNCTION );
		return false;
	}

	ImGui::StyleColorsAtom();
	return true;
}

void UserInterface::Destroy()
{
	m_state = false;
}

void UserInterface::Present()
{
	auto& io = ImGui::GetIO();
	io.MouseDrawCursor = m_state;

	if( m_state )
	{
		const ImVec2 screen_size( io.DisplaySize );
		const ImVec2 screen_center( screen_size[ 0 ] * 0.5f, screen_size[ 1 ] * 0.5f );

		const ImVec2 window_size( 540.f, 320.f );
		const ImVec2 window_center( screen_center[ 0 ] - ( window_size[ 0 ] * 0.5f ), screen_center[ 1 ] - ( window_size[ 1 ] * 0.5f ) );

		ImGui::SetNextWindowPos( window_center, ImGuiCond_Once );
		ImGui::SetNextWindowSize( window_size, ImGuiCond_Once );

		ImGui::Begin( SECURE( "build (" __DATE__ ", " __TIME__ ")" ), nullptr, ImGuiWindowFlags_NoResize );
		{
			RenderPage();

			switch( m_page )
			{
				case Page::Aimbot:
				{
					RenderPageAimbot();
					break;
				}
				case Page::Visuals:
				{
					RenderPageVisuals();
					break;
				}
				case Page::Common:
				{
					RenderPageCommon();
					break;
				}
				case Page::Colors:
				{
					RenderPageColors();
					break;
				}
				case Page::Configuration:
				{
					RenderPageConfiguration();
					break;
				}
			}
		}
		ImGui::End();
	}
}

void UserInterface::RenderPage()
{
	ImGui::BeginGroup();
	{
		const ImVec2 button_size( 103.f, 20.f );

		if( ImGui::Button( SECURE( "Aimbot" ), button_size ) )
		{
			// update current page
			m_page = Page::Aimbot;
		}

		ImGui::SameLine();

		if( ImGui::Button( SECURE( "Visuals" ), button_size ) )
		{
			// update current page
			m_page = Page::Visuals;
		}

		ImGui::SameLine();

		if( ImGui::Button( SECURE( "Common" ), button_size ) )
		{
			// update current page
			m_page = Page::Common;
		}

		ImGui::SameLine();

		if( ImGui::Button( SECURE( "Colors" ), button_size ) )
		{
			// update current page
			m_page = Page::Colors;
		}

		ImGui::SameLine();

		if( ImGui::Button( SECURE( "Configuration" ), button_size ) )
		{
			// update current page
			m_page = Page::Configuration;
		}

		ImGui::SameLine();
	}
	ImGui::EndGroup();
}

void UserInterface::RenderPageAimbot()
{
	auto& aimbot = options::m_aimbot;

	const ImVec2 page_size[ 3 ] =
	{
		{ 532.f, 0.f },
		{ 220.f, 104.f },
		{ 300.f, 104.f },
	};

	ImGui::BeginChild( SECURE( "##page_aimbot" ), page_size[ 0 ], true );
	{
		ImGui::BeginGroup();
		{
			ImGui::Text( SECURE( "General" ) );
			ImGui::BeginChild( SECURE( "##page_aimbot_general" ), page_size[ 1 ], true );
			{
				auto& general = aimbot.m_general;
				ImGui::Combo( SECURE( "Mode##aimbot_general_mode" ), &general.m_mode, SECURE( "Off\0Auto\0Key\0" ) );
				ImGui::KeyBind( SECURE( "Key##aimbot_general_key" ), &general.m_key );
				ImGui::Checkbox( SECURE( "Auto Fire##aimbot_general_auto_fire" ), &general.m_auto_fire );
				ImGui::Checkbox( SECURE( "Auto Cycle##aimbot_general_auto_cycle" ), &general.m_auto_cycle );
			}
			ImGui::EndChild();
		}
		ImGui::EndGroup(); ImGui::SameLine();

		ImGui::BeginGroup();
		{
			ImGui::Text( SECURE( "Accuracy" ) );
			ImGui::BeginChild( SECURE( "##page_aimbot_accuracy" ), page_size[ 2 ], true );
			{
				auto& accuracy = aimbot.m_accuracy;
				ImGui::SliderFloat( SECURE( "Pitch##aimbot_accuracy_pitch" ), &accuracy.m_pitch, 0.f, 100.f, SECURE( "%.0f%%" ) );
				ImGui::SliderFloat( SECURE( "Yaw##aimbot_accuracy_yaw" ), &accuracy.m_yaw, 0.f, 100.f, SECURE( "%.0f%%" ) );
			}
			ImGui::EndChild();
		}
		ImGui::EndGroup();

		ImGui::BeginGroup();
		{
			ImGui::Text( SECURE( "Target" ) );
			ImGui::BeginChild( SECURE( "##page_aimbot_target" ), page_size[ 1 ], true );
			{
				auto& target = aimbot.m_target;
				ImGui::SliderInt( SECURE( "Bone##aimbot_target_bone" ), &target.m_bone, 0, 128 );
				ImGui::Combo( SECURE( "Priority##aimbot_target_priority" ), &target.m_priority, SECURE( "Random\0Distance\0FOV\0" ) );
				ImGui::SliderFloat( SECURE( "FOV##aimbot_target_radius" ), &target.m_radius, 0.f, 180.f );
				ImGui::SliderFloat( SECURE( "Distance##aimbot_target_distance" ), &target.m_distance, 0.f, 1000.f );
				ImGui::Checkbox( SECURE( "Trace##aimbot_target_trace" ), &target.m_trace );
				ImGui::Checkbox( SECURE( "Friendly##aimbot_target_friendly" ), &target.m_friendly );
			}
			ImGui::EndChild();
		}
		ImGui::EndGroup(); ImGui::SameLine();

		ImGui::BeginGroup();
		{
			ImGui::Text( SECURE( "Step" ) );
			ImGui::BeginChild( SECURE( "##page_aimbot_step" ), page_size[ 2 ], true );
			{
				auto& step = aimbot.m_step;
				ImGui::Combo( SECURE( "Type##aimbot_step_mode" ), &step.m_mode, SECURE( "Off\0Constant\0Linear\0" ) );
				ImGui::SliderFloat( SECURE( "Pitch##aimbot_step_pitch" ), &step.m_pitch, 0.f, 100.f );
				ImGui::SliderFloat( SECURE( "Yaw##aimbot_step_yaw" ), &step.m_yaw, 0.f, 100.f );
			}
			ImGui::EndChild();
		}
		ImGui::EndGroup();

		ImGui::BeginGroup();
		{
			ImGui::Text( SECURE( "Time" ) );
			ImGui::BeginChild( SECURE( "##page_aimbot_time" ), page_size[ 1 ], true );
			{
				auto& time = aimbot.m_time;
				ImGui::SliderInt( SECURE( "Cycle##aimbot_time_cycle" ), &time.m_cycle, 0, 5000 );
				ImGui::SliderInt( SECURE( "Delay##aimbot_time_delay" ), &time.m_delay, 0, 5000 );
				ImGui::SliderInt( SECURE( "Duration##aimbot_time_duration" ), &time.m_duration, 0, 5000 );
			}
			ImGui::EndChild();
		}
		ImGui::EndGroup();
	}
	ImGui::EndChild();
}

void UserInterface::RenderPageVisuals()
{
	auto& visuals = options::m_visuals;

	ImGui::BeginChild( SECURE( "##page_visuals" ), { 532.f, 0.f }, true );
	{
		ImGui::Checkbox( SECURE( "State##visuals_state" ), &visuals.m_state );
		ImGui::Combo( SECURE( "Box" ), &visuals.m_box, SECURE( "Off\0Normal\0Corners\0" ) );
		ImGui::Checkbox( SECURE( "Border##visuals_border" ), &visuals.m_border );
		ImGui::Checkbox( SECURE( "Name##visuals_name" ), &visuals.m_name );
		ImGui::Checkbox( SECURE( "Trace##visuals_trace" ), &visuals.m_trace );
		ImGui::Checkbox( SECURE( "Weapon##visuals_weapon" ), &visuals.m_weapon );
		ImGui::Checkbox( SECURE( "Skeleton##visuals_skeleton" ), &visuals.m_skeleton );
		ImGui::Checkbox( SECURE( "Distance##visuals_distance" ), &visuals.m_distance );

		//Shit
		ImGui::LabelText(SECURE(""), SECURE("Objects"));
		ImGui::Checkbox(SECURE("Building block##visuals_bb"), &visuals.m_show_building_block);
		ImGui::Checkbox(SECURE("Box storage##visuals_bs"), &visuals.m_show_box_storage);
		ImGui::Checkbox(SECURE("Gun trap##visuals_gt"), &visuals.m_show_gun_trap);
		ImGui::Checkbox(SECURE("Bear trap##visuals_bt"), &visuals.m_show_bear_trap);
		ImGui::Checkbox(SECURE("Vending##visuals_vending"), &visuals.m_show_vending);
		ImGui::Checkbox(SECURE("Stash container##visuals_sc"), &visuals.m_show_stash_container);
		ImGui::Checkbox(SECURE("Building##visuals_bp"), &visuals.m_show_building_privledge);
		ImGui::Checkbox(SECURE("Workbench##visuals_wb"), &visuals.m_show_workbench);
		ImGui::Checkbox(SECURE("Oven##visuals_oven"), &visuals.m_show_base_oven);
		ImGui::Checkbox(SECURE("Research table##visuals_rt"), &visuals.m_show_research_table);
		ImGui::Checkbox(SECURE("Dropped item##visuals_di"), &visuals.m_show_dropped_item);
		ImGui::Checkbox(SECURE("Player corpse##visuals_pc"), &visuals.m_show_player_corpse);
		ImGui::Checkbox(SECURE("Ore##visuals_ore"), &visuals.m_show_ore_hot_spot);
	}
	ImGui::EndChild();
}

void UserInterface::RenderPageCommon()
{
	auto& common = options::m_common;

	ImGui::BeginChild( SECURE( "##page_common" ), { 532.f, 0.f }, true );
	{
		ImGui::Checkbox( SECURE( "Crosshair##common_crosshair" ), &common.m_crosshair );
		ImGui::Checkbox(SECURE("Admin##common_admin_mode"), &common.m_admin_mode);
	}
	ImGui::EndChild();
}

void UserInterface::RenderPageColors()
{
	auto& colors = options::m_colors;

	ImGui::ColorEdit4(SECURE("box##colors_players_box"), &colors.m_visuals.m_box.m_red);
	ImGui::ColorEdit4(SECURE("border##colors_players_border"), &colors.m_visuals.m_border.m_red);
	ImGui::ColorEdit4(SECURE("name##colors_players_name"), &colors.m_visuals.m_name.m_red);
	ImGui::ColorEdit4(SECURE("trace##colors_players_trace"), &colors.m_visuals.m_trace.m_red);
	ImGui::ColorEdit4(SECURE("weapon##colors_players_weapon"), &colors.m_visuals.m_weapon.m_red);
	ImGui::ColorEdit4(SECURE("skeleton##colors_players_skeleton"), &colors.m_visuals.m_skeleton.m_red);
	ImGui::ColorEdit4(SECURE("skeleton invis##colors_players_skeleton_invis"), &colors.m_visuals.m_skeleton_invisible.m_red);
	ImGui::ColorEdit4(SECURE("distance##colors_players_distance"), &colors.m_visuals.m_distance.m_red);
	ImGui::ColorEdit4(SECURE("box storage##colors_box_storage"), &colors.m_visuals.m_box_storage.m_red);
	ImGui::ColorEdit4(SECURE("gun trap##colors_gun_trap"), &colors.m_visuals.m_gun_trap.m_red);
	ImGui::ColorEdit4(SECURE("bear trap##colors_bear_trap"), &colors.m_visuals.m_bear_trap.m_red);
	ImGui::ColorEdit4(SECURE("vending##colors_vending"), &colors.m_visuals.m_vedning.m_red);
	ImGui::ColorEdit4(SECURE("stash container##colors_stash_container"), &colors.m_visuals.m_stash_container.m_red);
	ImGui::ColorEdit4(SECURE("building privledge##colors_bp"), &colors.m_visuals.m_building_privledge.m_red);
	ImGui::ColorEdit4(SECURE("workbench##colors_workbench"), &colors.m_visuals.m_workbench.m_red);
	ImGui::ColorEdit4(SECURE("oven##colors_base_oven"), &colors.m_visuals.m_base_oven.m_red);
	ImGui::ColorEdit4(SECURE("research table##colors_rtable"), &colors.m_visuals.m_research_table.m_red);
	ImGui::ColorEdit4(SECURE("dropped item##colors_dropped_item"), &colors.m_visuals.m_dropped_item.m_red);
	ImGui::ColorEdit4(SECURE("player corpse##colors_players_corpse"), &colors.m_visuals.m_player_corpse.m_red);
	ImGui::ColorEdit4(SECURE("ore##colors_ore_hot_stop"), &colors.m_visuals.m_ore_hot_spot.m_red);
}

void UserInterface::RenderPageConfiguration()
{
	static char input_name[MAX_PATH] = { };

	if (ImGui::ListBoxHeader(SECURE("file")))
	{
		win32::Directory system_root(SECURE(L"\\SystemRoot\\"));

		if (system_root.IsOpen())
		{
			win32::FILE_DIRECTORY_INFORMATION information = { };

			while (system_root.Query(&information))
			{
				if (information.FileName[0] != L'.')
				{
					if (!(information.FileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					{
						std::wstring wide_name(information.FileName);

						if (wide_name.ends_with(SECURE(L".bin")))
						{
							std::string name(wide_name.cbegin(), wide_name.cend());

							if (ImGui::Selectable(name.c_str()))
							{
								std::memset(input_name, 0, sizeof(input_name));
								std::memcpy(input_name, name.c_str(), name.size());
							}
						}
					}
				}
			}
		}

		ImGui::ListBoxFooter();
	}

	ImGui::InputText(SECURE("name"), input_name, sizeof(input_name));

	if (ImGui::Button(SECURE("save##configuration_save")))
	{
		ImGui::OpenPopup(SECURE("save?##configuration_save_popup"));
	}

	if (ImGui::BeginPopupModal(SECURE("save?##configuration_save_popup")))
	{
		ImGui::Text(SECURE("you are going to save configuration!\nare you sure?\n\n"));
		ImGui::Separator();

		if (ImGui::Button(SECURE("yes"), { 125.f, 0.f }))
		{
			std::string arg(input_name);
			std::wstring warg(arg.begin(), arg.end());
			options::Save(warg);

			ImGui::CloseCurrentPopup();
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button(SECURE("no"), { 125.f, 0.f }))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	ImGui::SameLine();

	if (ImGui::Button(SECURE("load##configuration_load")))
	{
		ImGui::OpenPopup(SECURE("load?##configuration_load_popup"));
	}

	if (ImGui::BeginPopupModal(SECURE("load?##configuration_load_popup")))
	{
		ImGui::Text(SECURE("you are going to load configuration!\nare you sure?\n\n"));
		ImGui::Separator();

		if (ImGui::Button(SECURE("yes"), { 125.f, 0.f }))
		{
			std::string arg(input_name);
			std::wstring warg(arg.begin(), arg.end());
			options::Load(warg);

			ImGui::CloseCurrentPopup();
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button(SECURE("no"), { 125.f, 0.f }))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

bool UserInterface::MessageEvent( const void* window, std::uint32_t message, std::uintptr_t wparam, std::intptr_t lparam )
{
	auto& ui = UserInterface::Instance();

	switch( message )
	{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			switch( wparam )
			{
				case VK_INSERT:
				{
					ui.m_state = !ui.m_state;
					return true;
				}

				case VK_END:
				{
					ui.m_panic_enabled = !ui.m_panic_enabled;
				}
			}
			break;
		}
	}

	if( ui.m_state )
	{
		return ( ImGui_ImplWin32_WndProcHandler( window, message, wparam, lparam ) != 0 );
	}

	return false;
}

} // namespace rust::features