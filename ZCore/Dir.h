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
#include <memory>

#include "FilePath.h"
#include "FSObject.h"
#include "DirImpl.h"

#pragma warning (disable : 4251)

namespace Zen
{
	class DirEnumerator;

	// This class is exported from the ZCore.dll
	class ZCORE_API Dir : public FSObject
	{
	public:
		//Dir(void);
		explicit Dir(const FilePath& path);
		
		static std::wstring GetCurrentDir();
		std::unique_ptr<DirEnumerator> Enumerator(const std::wstring& what = L"*");

		bool Create() override;
		bool Delete() override;

	private:
		std::shared_ptr<DirImpl> m_pImpl = nullptr;
	};
}

#pragma warning (default : 4251)
