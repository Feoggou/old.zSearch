#pragma once

#include <string>

namespace Zen
{
	class WinFilePath
	{
	public:
		static bool IsValid(const std::wstring& path);
		static bool IsRelative(const std::wstring& path);

		static wchar_t Delimiter();

	private:
		static wchar_t s_delimiter;
	};
}