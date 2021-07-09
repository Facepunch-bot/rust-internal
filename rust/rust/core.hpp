#pragma once

#include "../unity/sdk.hpp"

#include "steam.hpp"

namespace rust
{

extern std::uintptr_t m_unity_player;
extern std::uintptr_t m_game_assembly;
extern std::uintptr_t m_game_overlay_renderer;

extern D3D11SwapChain* m_d3d11_swap_chain;
extern IDXGISwapChain* m_swap_chain;

extern SteamUser32* m_steam_user32;

extern memory::VFTableHook::Unique m_swap_chain_hook;

extern std::uintptr_t m_dispatch_message;

extern std::uintptr_t m_present;
extern std::uintptr_t m_resize_buffers;

bool Create();
void Destroy();

D3D11SwapChain* GetD3D11SwapChain();

} // namespace rust

void DumpEntities();
void RenderEntities();