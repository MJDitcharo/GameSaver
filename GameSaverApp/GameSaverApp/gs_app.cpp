#include "gs_app.h"

namespace md
{
	void GsApp::run()
	{
		while (!gsWindow.shouldClose())
		{
			glfwPollEvents();
		}
	}
}