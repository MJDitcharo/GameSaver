#include "gs_window.h"

// std
#include <stdexcept>


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

	void md::GSWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create window surface");
		}
	}




}// namespace md