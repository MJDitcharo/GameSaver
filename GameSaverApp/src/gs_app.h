#pragma once

#include "gs_window.h"
#include "gs_pipeline.h"
#include "gs_device.h"

namespace md
{
	class GSApp
	{

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;
		
		void run();

	private:
		GSWindow gsWindow{WIDTH, HEIGHT, "Game Saver"};
		GSDevice gsDevice{ gsWindow };
		GSPipeline gsPipeline{gsDevice, "Shaders/VertexShader.spv", "Shaders/PixelShader.spv", GSPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
	};
}