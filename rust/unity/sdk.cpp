#include "sdk.hpp"

// 
// [ D3D11SwapChain ] implementation
// 

IDXGISwapChain* D3D11SwapChain::GetSwapChain() const
{
	return m_SwapChain;
}