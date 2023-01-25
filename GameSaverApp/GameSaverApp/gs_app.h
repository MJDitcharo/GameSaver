#pragma once

#include "gs_window.h"
#include "gs_pipeline.h"

namespace md
{
	class GsApp
	{

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;
		
		void run();

	private:
		GSWindow gsWindow{WIDTH, HEIGHT, "Game Saver"};

	};
}