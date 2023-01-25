#include "gs_window.h"

namespace md
{
	GSWindow::GSWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name}
	{
		initWindow();
	}

	GSWindow::~GSWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void md::GSWindow::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // tell glfw not to create opengl context
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);	// disable window resize after creation


		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}

}// namespace md