#pragma once
#ifndef BEDROCK_POOL_HPP
#define BEDROCK_POOL_HPP

// A pool allocator.

#include "types.hpp"
#include "traits.hpp"

namespace br {
	struct Pool: Allocator<Pool> {
		void free(void*) { }
		void alloc(br::u64) { }
	};

	// todo
	// - implement a memory pool/arena allocator
	// - design a common interface for allocators like this
}

#endif
