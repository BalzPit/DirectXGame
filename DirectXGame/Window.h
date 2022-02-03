#pragma once
#include <Windows.h> //in order to access win32 API



class Window
{
public:
	Window();
	//initialize the window
	bool init();
	//pick event msgs of the window from OS and dispatch them to windowprocedure
	bool broadcast();
	//release the window
	bool release();
	//indicate if window is currently running
	bool isRun();
	//retrieve the rectangle having same size as the window (NOT including size of title bprder)
	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	~Window();

protected:
	//window handle
	HWND m_hwnd;
	//boolean flag indicating if window is currently running
	bool m_is_run;
};

