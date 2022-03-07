#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

DeviceContext::DeviceContext(ID3D11DeviceContext * device_context) : m_device_context(device_context)
{

}



void DeviceContext::clearRenderTargetColor(SwapChain *swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = {red, green, blue, alpha};
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);

	//set in which render target we want to draw (we want to use the backbuffer of the swapchain)
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, NULL);
}



void DeviceContext::setVertexBuffer(VertexBuffer *vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;

	//set vertex buffer
	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	//set input layout object
	m_device_context->IASetInputLayout(vertex_buffer->m_layout);
}


//render a list of triangles on the screen
void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	//tell directX that our vertexBuffer passed with setVertexBuffer() is composed by a list of triangles
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//call directX Draw funciton
	m_device_context->Draw(vertex_count, start_vertex_index);
}



//set what area, or viewport, of the already set rendertarget we want to draw in
void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_device_context->RSSetViewports(1, &vp);
}



bool DeviceContext::release()
{
	m_device_context->Release();
	delete this;
	return true;
}



DeviceContext::~DeviceContext()
{
}
