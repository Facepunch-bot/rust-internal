#pragma once

#include "../include/auto.hpp"
#include "../include/base.hpp"
#include "../include/win32.hpp"

#include "../core/singleton.hpp"

#include "../win32/basic.hpp"
#include "../win32/image.hpp"
#include "../win32/math.hpp"
#include "../win32/process.hpp"
#include "../win32/string.hpp"
#include "../win32/time.hpp"
#include "../win32/trace.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS

#include "../imgui/imgui.hpp"
#include "../imgui/imgui_internal.hpp"

#include "../imgui/imgui_impl_win32.hpp"
#include "../imgui/imgui_impl_dx11.hpp"

#include "color.hpp"

namespace horizon::graphics
{

enum TextLayout : std::uint32_t
{
	TextLeft = 0x0000,
	TextRight = 0x0001,
	TextCenterV = 0x0002,
	TextCenterH = 0x0004,
	TextCenter = ( TextCenterV | TextCenterH ),
};

class Renderer : public core::Singleton< Renderer >
{
public:
	~Renderer();

public:
	bool Create( IDXGISwapChain* swap_chain );
	void Destroy();

	bool Begin();
	void End();

	void Lost();
	bool Reset();

	bool Intersect( const ImVec2& position );

	IDXGISwapChain* GetSwapChain() const;
	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetDeviceContext() const;

	const D3D11_VIEWPORT& GetViewport() const;

public:
	void DrawCircle( const ImVec2& center_screen, float radius, const Color& color, int segments = 12 );
	void DrawLine( const ImVec2& begin, const ImVec2& end, const Color& color );
	void DrawRect( const ImVec2& position, const ImVec2& size, const Color& color );

	void DrawBox( const ImVec2& position, const ImVec2& size, float thickness, const Color& color );
	void DrawBoxBorder( const ImVec2& position, const ImVec2& size, float thickness, const Color& color, const Color& border = Color::Black() );

	void DrawCornerBox( const ImVec2& position, const ImVec2& size, float thickness, const Color& color );
	void DrawCornerBoxBorder( const ImVec2& position, const ImVec2& size, float thickness, const Color& color, const Color& border = Color::Black() );

	void DrawText( const ImVec2& position, std::uint32_t layout, const Color& color, const char* const format, ... );
	void DrawTextShadow( const ImVec2& position, std::uint32_t layout, const Color& color, const char* const format, ... );
	void DrawTextBorder( const ImVec2& position, std::uint32_t layout, const Color& color, const Color& border, const char* const format, ... );

	void DrawTexture( ImTextureID texture_id, const ImVec2& position, const ImVec2& size, const Color& color = Color::White() );

protected:
	void DrawTextFormat( ImVec2 position, std::uint32_t layout, const Color& color, const Color& border, const char* const format, va_list arg_pack );

protected:
	bool CreateRenderTarget();
	void DestroyRenderTarget();

protected:
	// 
	// d3d11 data
	// 
	IDXGISwapChain* m_swap_chain = nullptr;
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_device_context = nullptr;

	// 
	// win32 object
	// 
	void* m_window = nullptr;

	// 
	// imgui data
	// 
	ImGuiContext* m_context = nullptr;
	ImDrawList* m_draw_list = nullptr;

	// 
	// render target view
	// 
	ID3D11RenderTargetView* m_render_target_view = nullptr;

	// 
	// viewport
	// 
	std::uint32_t m_viewport_count = 1;
	D3D11_VIEWPORT m_viewport = { };
};

} // namespace horizon::graphics