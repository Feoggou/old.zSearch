#pragma once

#include "DirIterator.h"
#include "FilePath.h"
#include "DirEnumeratorImpl.h"

#include <string>

namespace Zen
{
	class DirEnumerator
	{
	public:
		typedef DirIterator iterator;
		typedef const DirIterator const_iterator;

	public:
		DirEnumerator(const FilePath& path, const std::wstring& what);

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;

		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

	private:
		mutable uint64_t m_id = 0;
		FilePath m_path;

		std::unique_ptr<DirEnumeratorImpl> m_pImpl = nullptr;
	};
}