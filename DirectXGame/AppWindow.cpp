#include "AppWindow.h"


//vertex position structure
struct vec3
{
	float x, y, z;
};

//structure of our vertex type used to represent triangles' vertices
struct vertex
{
	vec3 position;
};



AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}



void AppWindow::onCreate()
{
	//superclass method
	Window::onCreate();
	
	//initialize the graphics engine
	GraphicsEngine::get()->init();
	//create engine's swap chain
	m_swap_chain= GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect(); //retrieve height and width of window
	m_swap_chain->init(this->m_hwnd, rc.right-rc.left, rc.bottom-rc.top);


	//create list of vertices of the triangle
	vertex list[] = 
	{
		//X - Y - Z
		{-0.5f, -0.5f, 0.0f}, //POS1
		{0.0f, 0.5f, 0.0f}, //POS2
		{0.5f, -0.5f, 0.0f} //POS3
	};

	//create vertexBuffer and load vertices
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();
	
	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}



void AppWindow::onUpdate()
{
	//superclass method
	Window::onUpdate();

	//get context and call clearrendertargetcolor
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	//set various data for the graphics pipeline

	RECT rc = this->getClientWindowRect(); //retrieve height and width of window
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top); //set viewport size same as window

	//shader stuff
	GraphicsEngine::get()->setShaders();

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//DRAW TRIANGLES
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);

	m_swap_chain->present(true);
}



void AppWindow::onDestroy()
{
	//superclass onDestroy method
	Window::onDestroy();

	//release vertex buffer
	m_vb->release();

	//release swap chain
	m_swap_chain->release();

	//release the engine
	GraphicsEngine::get()->release();
}
