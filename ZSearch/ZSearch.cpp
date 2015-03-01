// ZSearch.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ZSearch.h"
#include "../ZCore/DirIterator.h"
#include "../ZCore/Dir.h"

// This is an example of an exported variable
ZSEARCH_API int nZSearch=0;

// This is an example of an exported function.
ZSEARCH_API int fnZSearch(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see ZSearch.h for the class definition
ZSearch::ZSearch()
	: m_FileNameCS{ false }
{
}

ZResultItems&& ZSearch::operator()(const std::wstring& dirPath)
{
	//std::basic_ofstream<ZResultItem> os; std::char_traits;std::copy(
	ZResultItems items;
	Zen::Dir dir(dirPath);
	//Zen::DirIterator I

#if 0
	auto I = dir.begin();
	std::cbegin(dir);
	//for (auto& I = std::cbegin(dir); I != std::end(dir); ++I)
	{
	}
	for (const ZResultItem& a : dir)
	{
	}
#endif

	return std::move(items);
}