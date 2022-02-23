#pragma once

#include "Base.h"

#include "RendererContext.h"

class App
{
	SINGLETON( App );

public:
	 App()  { Run(); }
	~App()  {        }

	void Run();

private:

};
