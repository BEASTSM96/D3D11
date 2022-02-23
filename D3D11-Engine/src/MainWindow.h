#pragma once

#include "Base.h"

#include <glfw/glfw3.h>

class MainWindow
{
	SINGLETON( MainWindow );

public:
	MainWindow();
	~MainWindow();

	bool Update();

	void GetSize( int* pWidth, int* pHeight ) { glfwGetWindowSize( m_pWindow, pWidth, pHeight ); }
	void GetSize( uint32_t* pWidth, uint32_t* pHeight ) { glfwGetWindowSize( m_pWindow, ( int* )pWidth, ( int* )pHeight ); }

	int GetWidth() { return Width; }
	int GetHeight() { return Height; }

	HWND OSWindow();

private:
	GLFWwindow* m_pWindow;

	int Width = 1070;
	int Height = 700;

};