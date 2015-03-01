#pragma once

#include <string>
#include <memory>

namespace Zen
{
	// This class is exported from the ZCore.dll
	// mem resource management: allocates at ctor and automatically deallocates at dtor
	template <typename T, template <class> class Allocator = std::allocator>
	class MemResource
	{
	public:
		explicit MemResource(std::size_t size)
			: m_data{ NULL }
		{
			m_data = m_alloc.allocate(size);
		}

		const T* data() const { return m_data; }
		T* data() { return m_data; }

	private:
		T* m_data;

		typename Allocator<T> m_alloc;
	};
}