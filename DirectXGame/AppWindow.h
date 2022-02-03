#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"


//high level window
class AppWindow : public Window //INHERIT FROM WINDOW
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	SwapChain *m_swap_chain;
};

