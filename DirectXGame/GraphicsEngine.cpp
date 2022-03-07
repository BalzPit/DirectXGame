#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

GraphicsEngine::GraphicsEngine()
{
}



bool GraphicsEngine::init()
{
	//driver allows directX to execute the drawing functions. 
	//We have to loop through driver types until driver creation is successful
	D3D_DRIVER_TYPE driver_types[] =
	{
		//try different driver types, from best to worst
		D3D_DRIVER_TYPE_HARDWARE, //drawing calls are executed mainly on GPU, giving the best performance
		D3D_DRIVER_TYPE_WARP, //drawing calls all executed on CPU by using high-performance CPU instructions, like sse instructions
		D3D_DRIVER_TYPE_REFERENCE //like warp but really slow performance
	};
	//size of driver_types array
	UINT num_driver_types = ARRAYSIZE(driver_types);

	//indicate which feature level of DirectX to use
	D3D_FEATURE_LEVEL feature_levels[]=
	{
		//createDevice function needs feature level to be passed as an array, even if it has only one value
		D3D_FEATURE_LEVEL_11_0
	};
	//size of feature_levels array
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	//ID3D11DeviceContext *m_imm_context; //immediate devie context pointer
	//create the device from which we can get access to all resources necessary to draw on the screen
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		HRESULT res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		if (SUCCEEDED(res))
			break;

		++driver_type_index; //pre-increment gives better performance
	}

	if (FAILED(res))
	{
		return false;
	}

	//set instance of DeviceContext
	m_imm_device_context = new DeviceContext(m_imm_context);

	// this method returns instance of a class for which we pass its universally unique identifier. 
	// In this case we get the instance of DXGIDevice class. 
	// DXGI is the DirectX device infrastructure, a system that takes care of the low level tasks that can be 
	// independent of the DirectX graphics runtime, such as the Swap Chain
	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	//get instance of the DXGIAdapter class
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	//get instance of DXGIFactory class, this is what we need to create the SwapChain
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
	

	return true;
}



bool GraphicsEngine::release()
{
	//release all dxgi resources
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release();
	m_d3d_device->Release();
	return true;
}



SwapChain * GraphicsEngine::createSwapChain()
{
	return new SwapChain;
}



DeviceContext * GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

//create a new instance of VertexBufferuffer class
VertexBuffer * GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}



/*
 *	return singleton instance of GameEngine
 *
 *	Since engine is a static object, it will be put on the stack and created only ONCE at program initialization.
 *	Each time get() is called, it will always get the address of the same instance. 
 *	No more instances of this class will be created at runtime.
 */
GraphicsEngine * GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}



GraphicsEngine::~GraphicsEngine()
{
}


//=============================================== SHADER STUFF, will be explained better in later videos
bool GraphicsEngine::createShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	m_d3d_device->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	m_d3d_device->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
	return true;

}

bool GraphicsEngine::setShaders()
{
	m_imm_context->VSSetShader(m_vs, nullptr, 0);
	m_imm_context->PSSetShader(m_ps, nullptr, 0);
	return true;
}

void GraphicsEngine::getShaderBufferAndSize(void ** bytecode, UINT * size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (UINT)this->m_vsblob->GetBufferSize();

}