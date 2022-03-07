#include "Window.h"



Window::Window()
{
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE: // Event fired when the window is created
	{
		//get the "this" pointer passed in createWindowEx
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		//save the pointer "this" in a special data structure identified by hwnd
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);

		//set handle
		window->setHWND(hwnd);
		window->onCreate();
		break;
	}
	
	case WM_DESTROY: // Event fired when the window is destroyed
	{
		//recover the pointer "this" from the special data structure identified by hwnd
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0); // tell the system that this window has made a request to terminate
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}



bool Window::init()
{
	WNDCLASSEX wc;
	//set up WNDCLASSEX obj attributes
	wc.cbClsExtra= NULL;
	wc.cbSize= sizeof(WNDCLASSEX);
	wc.cbWndExtra= NULL;
	wc.hbrBackground= (HBRUSH)COLOR_WINDOW;
	wc.hCursor= LoadCursor(NULL, IDC_ARROW);
	wc.hIcon= LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance= NULL;
	wc.lpszClassName= "MyWindowClass"; //string necessary to identify this class of properties
	wc.lpszMenuName= "";
	wc.style= NULL;
	wc.lpfnWndProc= &WndProc;	//important property, window procedure with which we can handle events of the window (like initiation and destruction)

	//call win32 function that allows to register properties of windows we want to crete
	if (!::RegisterClassEx(&wc)) 
	{
		OutputDebugString("\nclass registration failed\n\n");
		//window registration failed
		return false;
	}

	//function that actually creates the window, returns a handle to the window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	if (!m_hwnd) 
	{
		OutputDebugString("\nwindow creation failed\n\n");
		//if window creation fails, it returns zero
		return false;
	}

	//show the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd); //redraws the content of window

	// window is innitialized and running, set this flag to true
	m_is_run = true;

	return true;
}



bool Window::broadcast()
{
	MSG msg;

	//since broadcast function is called in the main loop until the app is closed, we can place onUpdate here
	this->onUpdate();
	
	//get messages from OS messages queue until queue is empty
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		//translate and dispatch msg so window Procedure can process it
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	//don't allow the CPU to throttle, allow small pause to handle loop in a more relaxed way
	Sleep(0);

	return true;
}



bool Window::release()
{
	if (m_hwnd) 
	{
		//destroy the window
		if (!::DestroyWindow(m_hwnd)) 
		{
			OutputDebugString("\nwindow destruction failed\n\n");
			//something went wrong
			return false;
		}
	}
	return true;
}



bool Window::isRun()
{
	return m_is_run;
}



RECT Window::getClientWindowRect()
{
	RECT rc;
	//retrieve the rectangle corresponding to the internal size of the window (NOT including size of title bprder)
	::GetClientRect(this->m_hwnd, &rc);

	return rc;
}



void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}



void Window::onCreate()
{
}



void Window::onUpdate()
{
}



void Window::onDestroy()
{
	//set flag to false
	m_is_run = false;
}



Window::~Window()
{
}
