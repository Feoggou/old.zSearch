#pragma once

#include <cstdint>

namespace Zen
{
	class DirEnumeratorImpl
	{
	public:
		DirEnumeratorImpl();
		virtual ~DirEnumeratorImpl() = 0;

		virtual uint64_t First() const = 0;
		virtual uint64_t Last() const = 0;
		virtual uint64_t Invalid() const = 0;
	};
}