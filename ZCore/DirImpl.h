#pragma once

#include "FilePath.h"

namespace Zen
{
	class DirImpl
	{
	public:
		DirImpl(const FilePath& path);
		virtual ~DirImpl() = 0;

		virtual bool Create() = 0;
		virtual bool Delete() = 0;

	protected:
		FilePath m_path;
	};
}