#include "gs_app.h"

namespace md
{
	void GSApp::run()
	{
		while (!gsWindow.shouldClose())
		{
			glfwPollEvents();
		}
	}
}