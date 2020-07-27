#pragma once

#include <cstdint>

// Include the right version...
#ifdef _WIN32

#include "isaac32_engine.hpp"
namespace {
	typedef isaac32_engine IsaacEngine_impl_t;
}

#else

#include "isaac64_engine.hpp"
namespace {
	typedef isaac64_engine IsaacEngine_impl_t;
}

#endif

class IsaacEngine
{
private:
	IsaacEngine_impl_t _engine;
public:
	typedef IsaacEngine_impl_t::result_type result_type;

	IsaacEngine(result_type Seed = static_cast<result_type>(0)) :
		_engine(Seed)
	{

	}

	result_type Generate()
	{
		return _engine();
	}

	void Discard(uint64_t Count)
	{
		_engine.discard(Count);
	}
};