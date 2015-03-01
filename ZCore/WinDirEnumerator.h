#pragma once

#include "FilePath.h"
#include "DirEnumeratorImpl.h"

namespace Zen
{
	class WinDirEnumerator : public DirEnumeratorImpl
	{
	public:
		WinDirEnumerator(const FilePath& path, const std::wstring& what);
		~WinDirEnumerator();

		uint64_t First() const override;
		uint64_t Last() const override;
		uint64_t Invalid() const override { return Last(); }

	private:
		HANDLE	m_hFindeFile = INVALID_HANDLE_VALUE;
		FilePath m_path;
		const std::wstring m_what;
	};
}