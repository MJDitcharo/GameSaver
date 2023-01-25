#include "gs_pipeline.h"

// std
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace md
{
	GSPipeline::GSPipeline(const std::string& vertFilepath, const std::string& pixelFilepath)
	{
		createGraphicsPipeline(vertFilepath, pixelFilepath);
	}

	std::vector<char> GSPipeline::readFile(const std::string& filepath)
	{
		std::ifstream file(filepath, std::ios::ate | std::ios::binary);

		if (!file.is_open())
			throw std::runtime_error("failed to open file: " + filepath);


		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

	void GSPipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& pixelFilepath)
	{
		auto vertCode = readFile(vertFilepath);
		auto pixelCode = readFile(pixelFilepath);

		std::cout << "Vertex Shader Code Size: " << vertCode.size() << '\n';
		std::cout << "Pixel Shader Code Size: " << pixelCode.size() << '\n';
	}
}