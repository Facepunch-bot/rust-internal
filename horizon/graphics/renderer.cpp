#include "renderer.hpp"

#include "../memory/operation.hpp"

#include "../win32/trace.hpp"

namespace horizon::graphics
{

Renderer::~Renderer()
{
	Destroy();
}

bool Renderer::Create( IDXGISwapChain* swap_chain )
{
	m_swap_chain = swap_chain;

	if( !memory::IsAddressValid( m_swap_chain ) )
	{
		TRACE( "%s: m_swap_chain is not valid!", ATOM_FUNCTION );
		return false;
	}

	auto result = m_swap_chain->GetDevice( IID_PPV_ARGS( &m_device ) );

	if( FAILED( result ) )
	{
		TRACE( "%s: IDXGISwapChain::GetDevice( ... ) error! (0x%08X)", ATOM_FUNCTION, result );
		return false;
	}

	m_device->GetImmediateContext( &m_device_context );

	if( !memory::IsAddressValid( m_device_context ) )
	{
		TRACE( "%s: ID3D11Device::GetImmediateContext( ... ) error!", ATOM_FUNCTION );
		return false;
	}

	DXGI_SWAP_CHAIN_DESC swap_chain_desc = { };
	result = m_swap_chain->GetDesc( &swap_chain_desc );

	if( FAILED( result ) )
	{
		TRACE( "%s: IDXGISwapChain::GetDesc( ... ) error! (0x%08X)", ATOM_FUNCTION, result );
		return false;
	}

	m_window = swap_chain_desc.OutputWindow;

	if( !m_window )
	{
		TRACE( "%s: m_window is not valid!", ATOM_FUNCTION );
		return false;
	}

	m_context = ImGui::CreateContext();

	if( !memory::IsAddressValid( m_context ) )
	{
		TRACE( "%s: ImGui::CreateContext() error!", ATOM_FUNCTION );
		return false;
	}

	if( !ImGui_ImplWin32_Init( m_window ) )
	{
		TRACE( "%s: ImGui_ImplWin32_Init( ... ) error!", ATOM_FUNCTION );
		return false;
	}

	if( !ImGui_ImplDX11_Init( m_device, m_device_context ) )
	{
		TRACE( "%s: ImGui_ImplDX11_Init( ... ) error!", ATOM_FUNCTION );
		return false;
	}

	return CreateRenderTarget();
}

void Renderer::Destroy()
{
	// release device objects
	Lost();

	// release imgui objects
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	if( memory::IsAddressValid( m_context ) )
	{
		// destroy imgui
		ImGui::DestroyContext( m_context );
	}

	m_swap_chain = nullptr;
	m_device = nullptr;
	m_device_context = nullptr;

	m_window = nullptr;
	m_context = nullptr;
	m_draw_list = nullptr;

	m_render_target_view = nullptr;
}

bool Renderer::Begin()
{
	// sanity checks
	if( !memory::IsAddressValid( m_render_target_view ) )
	{
		return false;
	}

	// update viewport
	m_device_context->RSGetViewports( &m_viewport_count, &m_viewport );

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	m_draw_list = ImGui::GetBackgroundDrawList();
	return memory::IsAddressValid( m_draw_list );
}

void Renderer::End()
{
	ImGui::Render();

	// set render target
	m_device_context->OMSetRenderTargets( 1, &m_render_target_view, nullptr );

	// render imgui draw data
	ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );
}

void Renderer::Lost()
{
	// destroy imgui objects
	ImGui_ImplDX11_InvalidateDeviceObjects();

	// destroy render target
	DestroyRenderTarget();
}

bool Renderer::Reset()
{
	// reset render target
	if( !CreateRenderTarget() )
	{
		TRACE( "%s: CreateRenderTarget() error!", ATOM_FUNCTION );
		return false;
	}

	// reset imgui objects
	if( !ImGui_ImplDX11_CreateDeviceObjects() )
	{
		TRACE( "%s: ImGui_ImplDX11_CreateDeviceObjects() error!", ATOM_FUNCTION );
		return false;
	}

	return true;
}

bool Renderer::Intersect( const ImVec2& position )
{
	return ( position[ 0 ] >= 0.f &&
					 position[ 1 ] >= 0.f &&
					 position[ 0 ] <= m_viewport.Width &&
					 position[ 1 ] <= m_viewport.Height );
}

IDXGISwapChain* Renderer::GetSwapChain() const
{
	return m_swap_chain;
}

ID3D11Device* Renderer::GetDevice() const
{
	return m_device;
}

ID3D11DeviceContext* Renderer::GetDeviceContext() const
{
	return m_device_context;
}

const D3D11_VIEWPORT& Renderer::GetViewport() const
{
	return m_viewport;
}

void Renderer::DrawCircle( const ImVec2& center_screen, float radius, const Color& color, int segments /*= 12*/ )
{
	m_draw_list->AddCircle( { center_screen[ 0 ], center_screen[ 1 ] }, radius, ImColor( color.m_red, color.m_green, color.m_blue, color.m_alpha ), segments );
}

void Renderer::DrawLine( const ImVec2& begin, const ImVec2& end, const Color& color )
{
	m_draw_list->AddLine( { begin[ 0 ], begin[ 1 ] }, { end[ 0 ], end[ 1 ] }, ImColor( color.m_red, color.m_green, color.m_blue, color.m_alpha ) );
}

void Renderer::DrawRect( const ImVec2& position, const ImVec2& size, const Color& color )
{
	m_draw_list->AddRectFilled( { position[ 0 ], position[ 1 ] }, { position[ 0 ] + size[ 0 ], position[ 1 ] + size[ 1 ] }, ImColor( color.m_red, color.m_green, color.m_blue, color.m_alpha ), 0.f, ImDrawCornerFlags_None );
}

void Renderer::DrawBox( const ImVec2& position, const ImVec2& size, float thickness, const Color& color )
{
	DrawRect( position, { size[ 0 ], thickness }, color );
	DrawRect( position, { thickness, size[ 1 ] }, color );

	DrawRect( { position[ 0 ] + size[ 0 ], position[ 1 ] }, { thickness, size[ 1 ] }, color );
	DrawRect( { position[ 0 ], position[ 1 ] + size[ 1 ] }, { size[ 0 ] + thickness, thickness }, color );
}

void Renderer::DrawBoxBorder( const ImVec2& position, const ImVec2& size, float thickness, const Color& color, const Color& border /*= Color::Black()*/ )
{
	DrawBox( position, size, thickness, color );
	DrawBox( position - ImVec2( thickness, thickness ), size + ImVec2( thickness * 2.f, thickness * 2.f ), 1.f, border );
	DrawBox( position + ImVec2( thickness, thickness ), size - ImVec2( thickness * 2.f, thickness * 2.f ), 1.f, border );
}

void Renderer::DrawCornerBox( const ImVec2& position, const ImVec2& size, float thickness, const Color& color )
{
	const auto line_size = size * 0.25f;

	DrawRect( position, { line_size[ 0 ], thickness }, color ); // top left -> right
	DrawRect( position, { thickness, line_size[ 1 ] }, color ); // top left -> bottom

	DrawRect( { position[ 0 ], position[ 1 ] + size[ 1 ] - line_size[ 1 ] + thickness }, { thickness, line_size[ 1 ] }, color ); // bottom left -> top
	DrawRect( { position[ 0 ], position[ 1 ] + size[ 1 ] }, { line_size[ 0 ], thickness }, color ); // bottom left -> right

	DrawRect( { position[ 0 ] + size[ 0 ] - line_size[ 0 ] + thickness, position[ 1 ] }, { line_size[ 0 ], thickness }, color ); // top right -> left
	DrawRect( { position[ 0 ] + size[ 0 ], position[ 1 ] }, { thickness, line_size[ 1 ] }, color ); // top right -> bottom

	DrawRect( { position[ 0 ] + size[ 0 ] - line_size[ 0 ] + thickness, position[ 1 ] + size[ 1 ] }, { line_size[ 0 ], thickness }, color ); // bottom right -> left
	DrawRect( { position[ 0 ] + size[ 0 ], position[ 1 ] + size[ 1 ] - line_size[ 1 ] + thickness }, { thickness, line_size[ 1 ] }, color ); // bottom right -> top
}

void Renderer::DrawCornerBoxBorder( const ImVec2& position, const ImVec2& size, float thickness, const Color& color, const Color& border /*= Color::Black()*/ )
{
	const auto line_size = size * 0.25f;

	DrawRect( { position[ 0 ] - thickness, position[ 1 ] - thickness }, { line_size[ 0 ] + thickness * 2.f, 1.f + thickness * 2.f }, border ); // top left -> right
	DrawRect( { position[ 0 ] - thickness, position[ 1 ] - thickness }, { 1.f + thickness * 2.f, line_size[ 1 ] + thickness * 2.f }, border ); // top left -> bottom
	DrawRect( { position[ 0 ] - thickness, position[ 1 ] + size[ 1 ] - line_size[ 1 ] }, { 1.f + thickness * 2.f, line_size[ 1 ] + thickness * 2.f }, border ); // bottom left -> top
	DrawRect( { position[ 0 ] - thickness, position[ 1 ] + size[ 1 ] - thickness }, { line_size[ 0 ] + thickness * 2.f, 1.f + thickness * 2.f }, border ); // bottom left -> right
	DrawRect( { position[ 0 ] + size[ 0 ] - line_size[ 0 ], position[ 1 ] - thickness }, { line_size[ 0 ] + thickness * 2.f, 1.f + thickness * 2.f }, border ); // top right -> left
	DrawRect( { position[ 0 ] + size[ 0 ] - thickness, position[ 1 ] - thickness }, { 1.f + thickness * 2.f, line_size[ 1 ] + thickness * 2.f }, border ); // top right -> bottom
	DrawRect( { position[ 0 ] + size[ 0 ] - line_size[ 0 ], position[ 1 ] + size[ 1 ] - thickness }, { line_size[ 0 ] + thickness * 2.f, 1.f + thickness * 2.f }, border ); // bottom right -> left
	DrawRect( { position[ 0 ] + size[ 0 ] - thickness, position[ 1 ] + size[ 1 ] - line_size[ 1 ] }, { 1.f + thickness * 2.f, line_size[ 1 ] + thickness * 2.f }, border ); // bottom right -> top

	DrawCornerBox( position, size, thickness, color );
}

void Renderer::DrawText( const ImVec2& position, std::uint32_t layout, const Color& color, const char* const format, ... )
{
	va_list arg_pack = { };
	va_start( arg_pack, format );
	DrawTextFormat( position, layout, color, Color::Transparent(), format, arg_pack );
	va_end( arg_pack );
}

void Renderer::DrawTextShadow( const ImVec2& position, std::uint32_t layout, const Color& color, const char* const format, ... )
{
	const auto shadow = Color::Black( color.m_alpha );

	va_list arg_pack = { };
	va_start( arg_pack, format );
	DrawTextFormat( position + ImVec2( 1.f, 1.f ), layout, shadow, Color::Transparent(), format, arg_pack );
	DrawTextFormat( position, layout, color, Color::Transparent(), format, arg_pack );
	va_end( arg_pack );
}

void Renderer::DrawTextBorder( const ImVec2& position, std::uint32_t layout, const Color& color, const Color& border, const char* const format, ... )
{
	va_list arg_pack = { };
	va_start( arg_pack, format );
	DrawTextFormat( position, layout, color, border, format, arg_pack );
	va_end( arg_pack );
}

void Renderer::DrawTexture( ImTextureID texture_id, const ImVec2& position, const ImVec2& size, const Color& color /*= Color::White()*/ )
{
	m_draw_list->AddImage( texture_id, { position[ 0 ], position[ 1 ] }, { position[ 0 ] + size[ 0 ], position[ 1 ] + size[ 1 ] }, { 0.f, 0.f }, { 1.f, 1.f }, ImColor( color.m_red, color.m_green, color.m_blue, color.m_alpha ) );
}

void Renderer::DrawTextFormat( ImVec2 position, std::uint32_t layout, const Color& color, const Color& border, const char* const format, va_list arg_pack )
{
	const auto output_length = static_cast< std::size_t >( win32::vsprintf_s( nullptr, 0, format, arg_pack ) );

	if( !output_length )
	{
		return;
	}

	const auto output = std::make_unique< char[] >( output_length + 1 );
	win32::vsprintf_s( output.get(), output_length, format, arg_pack );

	const auto size = ImGui::CalcTextSize( output.get() );

	if( layout & TextRight )
	{
		position[ 0 ] -= size[ 0 ];
	}
	else if( layout & TextCenterH )
	{
		position[ 0 ] -= size[ 0 ] * 0.5f;
	}

	if( layout & TextCenterV )
	{
		position[ 1 ] -= size[ 1 ] * 0.5f;
	}

	if( border.m_alpha > 0.f )
	{
		DrawRect( position, { size[ 0 ], size[ 1 ] }, border );
	}

	m_draw_list->AddText( { position[ 0 ], position[ 1 ] }, ImColor( color.m_red, color.m_green, color.m_blue, color.m_alpha ), output.get() );
}

bool Renderer::CreateRenderTarget()
{
	ID3D11Texture2D* texture2d = nullptr;

	// try to acquire render target texture
	auto result = m_swap_chain->GetBuffer( 0, IID_PPV_ARGS( &texture2d ) );

	if( FAILED( result ) )
	{
		TRACE( "%s: IDXGISwapChain::GetBuffer( ... ) error! (0x%08X)", FN, result );
		return false;
	}

	// try to create render target
	result = m_device->CreateRenderTargetView( texture2d, nullptr, &m_render_target_view );

	// release texture
	memory::SafeRelease( texture2d );

	if( FAILED( result ) )
	{
		TRACE( "%s: ID3D11Device::CreateRenderTargetView( ... ) error! (0x%08X)", FN, result );
		return false;
	}

	return true;
}

void Renderer::DestroyRenderTarget()
{
	memory::SafeRelease( m_render_target_view );
}

} // namespace horizon::graphics