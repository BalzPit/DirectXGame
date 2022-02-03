#include "AppWindow.h" 

int main()
{
	AppWindow app;

	if (app.init())
	{
		OutputDebugString("\nhello\n\n");
		//GAME LOOP
		while (app.isRun())
		{
			app.broadcast();
		}
	}


	return 0;
}