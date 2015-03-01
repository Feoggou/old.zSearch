#pragma once

#include <string>

namespace Zen
{
	class FileInfo
	{
	public:
		FileInfo();
		~FileInfo();

		std::wstring DisplayName() const { return std::wstring(L"file"); }
	};
}