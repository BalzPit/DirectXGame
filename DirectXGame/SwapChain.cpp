#include "SwapChain.h"
#include "GraphicsEngine.h"



SwapChain::SwapChain()
{
}



bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device *device = GraphicsEngine::get()->m_d3d_device;
	
	//pointer to swapchain descriptor
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc)); //avoid dirty memory 
	
	// we need 2 buffers, front buffer and back buffer. But in windowed mode the swapchain only needs one buffer,
	// the front buffer is already present, and it's the desktop itself, handled by the desktop window manager of the OS
	desc.BufferCount = 1;
	//size of the window
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	//pixel format of the frame bufers of the swapchain
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //8 bits for each value of R,G,B and alpha
	desc.BufferDesc.RefreshRate.Numerator = 60; // 60Hz refresh rate
	desc.BufferDesc.RefreshRate.Denominator = 1;
	//decide how to use the buffers of our swapchain, we will treat them as render targets
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	//create the swap chain for the window indicated by HWND window handle parameter
	HRESULT hr= GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);
	if (FAILED(hr)) 
	{
		return false;
	}

	//get back buffer
	ID3D11Texture2D *buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D),(void**)&buffer);
	if (FAILED(hr))
	{
		return false;
	}

	//create render target view from the device
	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool SwapChain::present(bool vsync)
{
	//if sync interval is 0 the presentation occours immediately without any synchrnonization
	m_swap_chain->Present(vsync, NULL);

	return true;
}



bool SwapChain::release()
{
	//release the swap chain instance
	m_swap_chain->Release();
	delete this;
	return true;
}



SwapChain::~SwapChain()
{
}
