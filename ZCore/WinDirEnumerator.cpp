#include "stdafx.h"
#include "WinDirEnumerator.h"

using namespace Zen;

WinDirEnumerator::WinDirEnumerator(const FilePath& path, const std::wstring& what)
	: m_path(path),
	m_what(what)
{
}


WinDirEnumerator::~WinDirEnumerator()
{
}

uint64_t WinDirEnumerator::First() const
{
	std::wstring fullSearchStr = m_path.ToWString() + FilePath::Delimiter() + m_what;

	LPCTSTR path = fullSearchStr.data();
	WIN32_FIND_DATA findData;

	HANDLE hFindFile = FindFirstFile(path, &findData);
	if (INVALID_HANDLE_VALUE == hFindFile) {
		DWORD error = GetLastError();

		if (error == ERROR_FILE_NOT_FOUND)
		{
			return reinterpret_cast<uint64_t>(INVALID_HANDLE_VALUE);
		}

		throw error;
	}

	return reinterpret_cast<uint64_t>(hFindFile);
}

uint64_t WinDirEnumerator::Last() const
{
	return reinterpret_cast<uint64_t>(INVALID_HANDLE_VALUE);
}