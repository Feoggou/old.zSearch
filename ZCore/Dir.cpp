// ZCore.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Dir.h"
#include "WinDir.h"
#include "DirEnumerator.h"

#if WIN32
#include "WinDir.h"
#endif

using namespace Zen;

Dir::Dir(const FilePath& path)
	: FSObject(path),
#if WIN32
	m_pImpl(new WinDir(path))
#else
#error NOT IMPLEMENTED
#endif
{
}

std::wstring Dir::GetCurrentDir()
{
	return WinDir::GetCurrentDir();
}

std::unique_ptr<DirEnumerator> Dir::Enumerator(const std::wstring& what)
{
	const auto& path = GetPath();
	return std::unique_ptr<Zen::DirEnumerator>(new DirEnumerator(path, what));
}


bool Dir::Create()
{
	if (!m_pImpl->Create())
	{
		return nullptr;
	}

	return FSObject::Create();
}

bool Dir::Delete()
{
	if (!m_pImpl->Delete())
	{
		return nullptr;
	}

	return FSObject::Delete();
}