#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ZCORE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ZCORE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ZCORE_EXPORTS
#define ZCORE_API __declspec(dllexport)
#else
#define ZCORE_API __declspec(dllimport)
#endif

#include <memory>

#include "FileInfo.h"

#pragma warning (disable : 4251)

namespace Zen
{
	class DirEnumerator;

	class ZCORE_API DirIterator
	{	
	private:
		DirIterator(const DirEnumerator* pEnum, uint64_t id);

	public:
		DirIterator();
		~DirIterator();

		FileInfo operator*() { return FileInfo(); }
		DirIterator& operator++() { return *this; }
		DirIterator& operator++(int) { return *this; }

		static uint64_t InvalidId();

		friend class DirEnumerator;
		friend bool operator== (const DirIterator&, const DirIterator&);

	private:
		const DirEnumerator* m_pEnum = nullptr;
		uint64_t m_id = 0;
	};

	inline bool operator== (const DirIterator& l, const DirIterator& r)
	{
		return (l.m_pEnum == r.m_pEnum && l.m_id == r.m_id);
	}

	inline bool operator!= (const DirIterator& l, const DirIterator& r)
	{
		return !(operator==(l, r));
	}
}

#pragma warning (default : 4251)