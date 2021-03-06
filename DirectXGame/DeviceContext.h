#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;

class DeviceContext
{
public:
	//constructor
	DeviceContext(ID3D11DeviceContext *device_context);
	void clearRenderTargetColor(SwapChain *swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer *vertex_buffer);
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);

	//get context attribute and call release method
	bool release();

	~DeviceContext();

private:
	ID3D11DeviceContext *m_device_context;
};

