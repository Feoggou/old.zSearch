#pragma once

#include "FSObject.h"

namespace Zen
{
	class FilePath;
	class Dir;

	class File : public FSObject
	{
	public:
		File(const FilePath& path) : FSObject(path) {}
		File(const Dir& parent, const std::wstring& displayName)
			: FSObject(parent.GetPath() + displayName)
		{}
	};
}