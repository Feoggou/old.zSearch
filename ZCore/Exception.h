#pragma once

#include <exception>

namespace Zen
{
	class Logger;

	class Exception : public std::exception
	{
	public:
		Exception();
		Exception(const char* const& message);
		Exception(const char* const& message, int);
		Exception(const exception& right);

		Exception& operator=(const Exception& right);

		virtual const char *what() const { return nullptr; }

		static void SetLogger(Logger* logger) { s_pLogger = logger; }
		static Logger* GetLogger() { return s_pLogger; }

	private:
		static Logger* s_pLogger;
	};
};