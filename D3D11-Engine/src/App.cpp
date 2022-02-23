#include "App.h"
#include "MainWindow.h"

void App::Run()
{
	MainWindow::Get();

	RendererContext::Get();

	while( MainWindow::Get().Update() )
	{
		RendererContext::Get().Render();
	}

}
