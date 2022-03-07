#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	//initialize swapchain for a window
	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsync);

	//release the swapchain
	bool release();

	~SwapChain();
private:
	IDXGISwapChain *m_swap_chain;	//pointer to the swap chain instance
	ID3D11RenderTargetView *m_rtv;	//render target of the swap chain

private: 
	friend class DeviceContext;
};

