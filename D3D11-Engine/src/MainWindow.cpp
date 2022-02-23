#include "MainWindow.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>

#include <iostream>

void GLFWErrorCB( int pErrorCode, const char* pDescription )
{
	std::cout << "GLFW Error " << pDescription << "\n";
}

MainWindow::MainWindow()
{
	glfwSetErrorCallback( GLFWErrorCB );

	if( !glfwInit() )
		return;

	glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );

	m_pWindow = glfwCreateWindow( Width, Height, "D3D11 Engine", nullptr, nullptr );
}

MainWindow::~MainWindow()
{

}

bool MainWindow::Update()
{
	glfwPollEvents();

	return !glfwWindowShouldClose( m_pWindow );
}

HWND MainWindow::OSWindow()
{
	return glfwGetWin32Window( m_pWindow );
}