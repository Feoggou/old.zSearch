#pragma once

#include <string>

namespace Zen
{
	class Logger
	{
	protected:
		Logger();

	public:
		static Logger* Create(const std::string& path);
	};
}