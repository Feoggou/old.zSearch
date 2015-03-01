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

#include "FilePath.h"

namespace Zen
{
	class ZCORE_API FSObject
	{
	public:
		enum State
		{
			State_Unkown,
			State_Exists,
			State_DoesNotExist
		};

	public:
		FSObject() = delete;
		virtual ~FSObject() = 0 {}

		explicit FSObject(const FilePath& path) : m_path(path), m_state(State_Unkown) {}

		const FilePath& GetPath() const { return m_path; }

		bool Exists() const { return (m_state == State_Exists); }
		virtual bool Create() { m_state = State_Exists; return true; }
		virtual bool Delete() { m_state = State_DoesNotExist; return true; }

	private:
		FilePath m_path;
		State m_state;
	};
}