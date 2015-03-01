#include "stdafx.h"
#include "WinFilePath.h"

/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/aa365247(v=vs.85).aspx
*/

using namespace Zen;

wchar_t WinFilePath::s_delimiter = '\\';

bool WinFilePath::IsRelative(const std::wstring& path)
{
	if (!WinFilePath::IsValid(path))
	{
		return false;
	}

	std::size_t size = path.size();
	if (size < 2)
	{
		//a path like "M" may be a directory M - relative path.
		return true;
	}

	if (path[0] == '\\')
	{
		return false;
	}

	//size >= 2
	if (path[1] == ':')
	{
		return false;
	}

	return true;
}

bool WinFilePath::IsValid(const std::wstring& path)
{
	if (path.empty()) {
		return false;
	}

	if (iswblank(path.front()) ||
		iswblank(path.back()))
	{
		return false;
	}

	if ('.' == path.back())
	{
		return false;
	}

	return true;
}

wchar_t WinFilePath::Delimiter()
{
	return WinFilePath::s_delimiter;
}