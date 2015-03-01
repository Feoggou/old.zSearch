#include "stdafx.h"
#include "DirIterator.h"

using namespace Zen;

DirIterator::DirIterator(const DirEnumerator* pEnum, uint64_t id)
	: m_pEnum(pEnum),
	m_id(id)
{
}

DirIterator::DirIterator()
	: m_id(DirIterator::InvalidId())
{
}


DirIterator::~DirIterator()
{
	
}

uint64_t DirIterator::InvalidId()
{
	return reinterpret_cast<uint64_t>(INVALID_HANDLE_VALUE);
}