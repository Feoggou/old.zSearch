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

#include <string>

#pragma warning (disable : 4251)

namespace Zen
{
	class ZCORE_API FilePath
	{
	public:
		//FilePath();
		FilePath(const std::wstring& str) : m_str(str) {}
		FilePath(const wchar_t* str) : m_str(str) {}

		bool IsRelative() const;
		bool IsValid() const;

		const std::wstring& ToWString() const;

		static wchar_t Delimiter();

	private:
		std::wstring m_str;
	};

	inline bool operator== (const FilePath& l, const FilePath& r)
	{
		return l.ToWString() == r.ToWString();
	}

	inline FilePath operator+ (const FilePath& parent, const std::wstring& displayName)
	{
		FilePath path(parent.ToWString() + FilePath::Delimiter() + displayName);

		return std::move(path);
	}
}

#pragma warning (default : 4251)