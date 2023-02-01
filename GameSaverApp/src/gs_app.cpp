#include "gs_app.h"


// std
#include <stdexcept>
#include <array>

namespace md
{

	GSApp::GSApp()
	{
		loadModels();
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	GSApp::~GSApp() { vkDestroyPipelineLayout(gsDevice.device(), pipelineLayout, nullptr); }


	void GSApp::run()
	{
		while (!gsWindow.shouldClose())
		{
			glfwPollEvents();
			drawFrame();
		}

		vkDeviceWaitIdle(gsDevice.device());
	}

	void GSApp::loadModels()
	{
		std::vector<GSModel::Vertex> vertices
		{
			{{0.0f, -0.5f}, {1.0f, 0.0f,0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};

		gsModel = std::make_unique<GSModel>(gsDevice, vertices);
	}

	void GSApp::createPipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(gsDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw std::runtime_error("failed to create pipeline layout");
	}

	void GSApp::createPipeline()
	{
		auto pipelineConfig = GSPipeline::defaultPipelineConfigInfo(gsSwapChain.width(), gsSwapChain.height());
		pipelineConfig.renderPass = gsSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		gsPipeline = std::make_unique<GSPipeline>(gsDevice, "Shaders/VertexShader.spv", "Shaders/PixelShader.spv", pipelineConfig);
	}

	void GSApp::createCommandBuffers()
	{
		commandBuffers.resize(gsSwapChain.imageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = gsDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(gsDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate command buffers");

		for (size_t i = 0; i < commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
				throw std::runtime_error("failed to begin recording command buffer");


			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = gsSwapChain.getRenderPass();
			renderPassInfo.framebuffer = gsSwapChain.getFrameBuffer(i);

			renderPassInfo.renderArea.offset = { 0,0 };
			renderPassInfo.renderArea.extent = gsSwapChain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.1f, 0.1f,0.1f ,1.0f };
			clearValues[1].depthStencil = { 1.0f, 0 };
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			// VK_SUBPASS_CONTENTS_INLINE is used when not using secondary cmd buffers
			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			gsPipeline->bind(commandBuffers[i]);
			gsModel->bind(commandBuffers[i]);
			gsModel->draw(commandBuffers[i]);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to record command buffer");
		}

	}

	void GSApp::drawFrame()
	{
		uint32_t imageIndex;
		auto result = gsSwapChain.acquireNextImage(&imageIndex);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("failed to acquire next swap chain image");

		result = gsSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS)
			throw std::runtime_error("failed to present swap chain image");
	}

}