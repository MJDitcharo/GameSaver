#pragma once


#include "gs_device.h"

// std
#include <string>
#include <vector>

namespace md
{

	struct PipelineConfigInfo {
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class GSPipeline
	{
	public:
		GSPipeline(
			GSDevice& device, 
			const std::string& vertFilepath, 
			const std::string& pixelFilepath, 
			const PipelineConfigInfo configInfo);

		~GSPipeline();

		GSPipeline(const GSPipeline&) = delete;
		void operator=(const GSPipeline&) = delete;


		static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

	private:
		static std::vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline(
			const std::string& vertFilepath, 
			const std::string& pixelFilepath, 
			const PipelineConfigInfo configInfo);

		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		GSDevice& gsDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule pixelShaderModule;
	};

}