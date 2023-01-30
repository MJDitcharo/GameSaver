#pragma once


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace md
{
	class GSWindow
	{
	public:
		GSWindow(int w, int h, std::string name);
		~GSWindow();

		GSWindow(const GSWindow&) = delete;
		GSWindow& operator=(const GSWindow&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(window); };

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	private:
		void initWindow();

		const int width;
		const int height;

		std::string windowName;

		GLFWwindow* window;

	};
}// namespace md