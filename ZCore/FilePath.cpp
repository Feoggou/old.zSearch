#include "stdafx.h"

#include "FilePath.h"
#include "WinFilePath.h"

using namespace Zen;

bool FilePath::IsRelative() const
{
	return WinFilePath::IsRelative(m_str);
}

bool FilePath::IsValid() const
{
	return WinFilePath::IsValid(m_str);
}

wchar_t FilePath::Delimiter()
{
	return WinFilePath::Delimiter();
}

const std::wstring& FilePath::ToWString() const
{
	return m_str;
}