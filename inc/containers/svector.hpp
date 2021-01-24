#pragma once
#ifndef BEDROCK_STATIC_VECTOR_HPP
#define BEDROCK_STATIC_VECTOR_HPP

// A vector with a fixed, static size.

#include "../core/type.hpp"
#include "../core/trait.hpp"

namespace br {
	// vector with fixed capacity
	template <typename T, br::size_t N>
	struct SVector: Container<SVector<T, N>> {
		T buffer[N];
		br::size_t used;   // Capacity used so far.
	};


	template <typename T, br::size_t N>
	auto& svec_at(const SVector<T, N>& vec, br::index_t i) {
		return vec.buffer[i];
	}


	template <typename T, typename V>
	auto& svec_append(const SVector<T>& vec, const V& value) {
		// append `value` and grow if needed.
	}

	// todo:
	// - svec_size    : return the number of elements in vector
	// - svec_extend  : append a vector to another vector
	// - svec_insert  : insert element at specific index
	// - svec_remove  : remove element at specific index
	// - svec_pop     : pop last element
	// - svec_eq      : compare 2 vectors

	// other:
	// iterators  : come up with a decent interface for iterators
	// allocators : come up with a decent interface for allocators
}

#endif


