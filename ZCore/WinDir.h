#pragma once

#include <string>

#include "DirImpl.h"

namespace Zen
{
	class WinDir : public DirImpl
	{
	public:
		WinDir(const FilePath& path);

		bool Create() override;
		bool Delete() override;

		static std::wstring GetCurrentDir();
	};
}