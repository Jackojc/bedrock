#pragma once
#ifndef BEDROCK_POOL_HPP
#define BEDROCK_POOL_HPP

// A pool allocator.

#include <cstdlib>

#include "../core/type.hpp"
#include "../core/trait.hpp"

namespace br {
	struct Pool: Allocator<Pool> {
		br::size_t capacity;

		void* buffer;
		void* next;


		void release(void*) {
			// We don't release memory.
		}

		void* allocate(br::size_t sz) {
			void* out = next;
			next = static_cast<char*>(next) + sz;
			return out;
		}
	};


	Pool pool_create(br::size_t initial_size) {
		Pool p;

		p.capacity = initial_size;
		p.buffer = std::malloc(initial_size);
		p.next = p.buffer;

		return p;
	}

	void pool_destroy(Pool& p) {
		std::free(p.buffer);

		p.capacity = 0;
		p.buffer = nullptr;
		p.next = nullptr;
	}

	// todo
	// - implement a memory pool/arena allocator
	// - design a common interface for allocators like this
}

#endif
