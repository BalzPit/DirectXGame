#pragma once
#include <d3d11.h> //DirectX11 API

class SwapChain;


class GraphicsEngine
{
public:
	GraphicsEngine();
	//initialise the GraphicsEngine and DirectX Device 
	bool init();
	//release all loaded resources
	bool release();
	~GraphicsEngine();

public:
	SwapChain *createSwapChain();
public:
	static GraphicsEngine *get(); //MAKE GraphhicsEngine class a SINFGLETON

private:
	ID3D11Device *m_d3d_device; //directX device pointer
	D3D_FEATURE_LEVEL m_feature_level; //indicate which of the input feature levels has been chosen during device creation
	ID3D11DeviceContext *m_imm_context; //immediate devie context pointer
private:
	IDXGIDevice *m_dxgi_device;
	IDXGIAdapter *m_dxgi_adapter;
	IDXGIFactory *m_dxgi_factory;
private:
	friend class SwapChain; // make SwapChain a friend class, this way we can access private members 
							// of GraphicsEngine from SwapChain but not exposing them to all classes
};

