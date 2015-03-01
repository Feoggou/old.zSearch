#include "stdafx.h"
#include "DirEnumerator.h"

#if WIN32
#include "WinDirEnumerator.h"
#else
#endif

using namespace Zen;

DirEnumerator::DirEnumerator(const FilePath& path, const std::wstring& what)
	: m_path(path),
#if WIN32
	m_pImpl(new WinDirEnumerator(path, what))
#else
#error NOT IMPLEMENTED
#endif
{
	m_id = m_pImpl->Invalid();
}

DirEnumerator::iterator DirEnumerator::begin()
{
	return cbegin();
}

DirEnumerator::const_iterator DirEnumerator::begin() const
{
	return cbegin();
}

DirEnumerator::const_iterator DirEnumerator::cbegin() const
{
	if (this->m_id == m_pImpl->Invalid())
	{
		try
		{
			m_id = m_pImpl->First();
		}

		//catch all for the moment
		catch (...)
		{
		}
	}

	return iterator(this, m_id);
}

DirEnumerator::iterator DirEnumerator::end()
{
	return iterator(this, m_pImpl->Last());
}

DirEnumerator::const_iterator DirEnumerator::end() const
{
	return iterator(this, m_pImpl->Last());
}

DirEnumerator::const_iterator DirEnumerator::cend() const
{
	return iterator(this, m_pImpl->Last());
}

