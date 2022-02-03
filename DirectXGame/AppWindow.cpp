#include "AppWindow.h"


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

	RECT rc = this->getClientWindowRect(); //to retrieve height and width of window
	m_swap_chain->init(this->m_hwnd, rc.right-rc.left, rc.bottom-rc.top);
}



void AppWindow::onUpdate()
{
	//superclass method
	Window::onUpdate();
}



void AppWindow::onDestroy()
{
	//superclass onDestroy method
	Window::onDestroy();

	//release swap chain
	m_swap_chain->release();

	//release the engine
	GraphicsEngine::get()->release();
}
