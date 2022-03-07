#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer() : m_buffer(0), m_layout(0)
{
}


/**
 * create the vertex buffer
 *
 * @param list_vertices pointer to the list of vertices
 * @param size_vertex size (in bytes) of the vertex type
 * @param size_list number of vertices in the list
 * @param shader_byte_code pointer to the bytecode of a shader 
 * @param size_byte_shader size in bytes of the shader bytecode
 * 
 * @return true if the operation was successful, false otherwise.
 */
bool VertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void *shader_byte_code, size_t size_byte_shader)
{
	//since load can be used multiple times to load different lists of vertices, release the two resources, new lists will need new ones
	if (m_buffer)m_buffer->Release();
	if (m_layout)m_layout->Release();

	//buffer descriptor object in which we set data relative to our buffer
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;	//indicate whether buffer is accessible by CPU and/or GPU
	buff_desc.ByteWidth = size_vertex * size_list;	//indicates the size in bytes of our buffer
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//tell directx how to bind this buffer to the graphics pipeline
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	//subresource data object
	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	//create the vertex buffer from the directX device, so, get it from GraphicsEngine
	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	//descriptor obj in which to add all info about the attributes of our vertex type
	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFEST - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		//at the moment we don't need special attributes, we will only use the position atttribute
	};

	UINT size_layout = ARRAYSIZE(layout); //gt number of attributes

	//create the input layout
	if(FAILED(GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
	{
		return false;
	}

	return true;
}



//return number of vertices to draw
UINT VertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}



bool VertexBuffer::release()
{
	m_layout->Release();
	m_buffer->Release();
	delete this;

	return true;
}

VertexBuffer::~VertexBuffer()
{
}
