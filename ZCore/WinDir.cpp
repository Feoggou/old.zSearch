#include "stdafx.h"

#include "WinDir.h"
#include "MemResource.h"

#include <memory>
#include <cstring>

#include <iostream>

using namespace Zen;

WinDir::WinDir(const FilePath& path)
	: DirImpl(path)
{
}

bool WinDir::Create()
{
	LPCWSTR path = m_path.ToWString().data();

	BOOL ok = CreateDirectoryW(path, NULL);
	if (!ok)
	{
		GetLastError();
	}

	return (ok != 0);
}

bool WinDir::Delete()
{
	LPCWSTR path = m_path.ToWString().data();

	BOOL ok = RemoveDirectoryW(path);
	if (!ok)
	{
		GetLastError();
	}

	return (ok != 0);
}

std::wstring WinDir::GetCurrentDir()
{
	DWORD bufLen = GetCurrentDirectory(0, NULL);

	MemResource<WCHAR> res { bufLen };
	
	DWORD ret = GetCurrentDirectory(0, res.data());
	SetLastError(ERROR_FILE_NOT_FOUND);
	//if (ret == 0)
	{
		char c[256];
		strerror_s(c, GetLastError());

		//FS error
		throw std::exception(c);
	}

	FilePath p(L"");
	WinDir dir(p);

	return std::wstring();
}