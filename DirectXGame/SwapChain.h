#pragma once
#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();
	//initialize swapchain for a window
	bool init(HWND hwnd, UINT width, UINT height);
	//release the swapchain
	bool release();

	~SwapChain();
private:
	IDXGISwapChain *m_swap_chain;	//pointer to the swap chain instance
};

