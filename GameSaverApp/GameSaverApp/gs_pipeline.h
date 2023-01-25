#pragma once

#include <string>
#include <vector>

namespace md
{
	class GSPipeline
	{
	public:
		GSPipeline(const std::string& vertFilepath, const std::string& pixelFilepath);

	private:
		static std::vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline(const std::string& vertFilepath, const std::string& pixelFilepath);
	};

}