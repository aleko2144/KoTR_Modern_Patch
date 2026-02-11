#pragma once

#include <cstdint>

template<typename LinkT>
struct IntrusiveQueue
{
	LinkT* m_persistent;
	LinkT* m_staging;
	uint32_t m_mergeCounter;
};
