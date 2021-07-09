#pragma once

#include "../../unity/sdk.hpp"

namespace rust::features
{

class UserInterface : public core::Singleton< UserInterface >
{
protected:
	enum class Page
	{
		Aimbot,
		Visuals,
		Common,
		Colors,
		Configuration,
	};

public:
	~UserInterface();

public:
	bool Create();
	void Destroy();

public:
	void Present();

protected:
	void RenderPage();

	void RenderPageAimbot();
	void RenderPageVisuals();
	void RenderPageCommon();
	void RenderPageColors();
	void RenderPageConfiguration();

protected:
	static bool MessageEvent( const void* window, std::uint32_t message, std::uintptr_t wparam, std::intptr_t lparam );

public:
	bool m_panic_enabled = false;

protected:
	bool m_state = false;
	Page m_page = Page::Aimbot;
};

} // namespace rust::features