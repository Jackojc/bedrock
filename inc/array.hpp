#ifndef BEDROCK_ARRAY_HPP
#define BEDROCK_ARRAY_HPP

// A wrapper around C-style arrays which doesn't decay to a pointer.

#include "types.hpp"
#include "traits.hpp"

namespace br {
	template <typename T, br::size_t N>
	struct Array: Container<Array<T, N>> {
		T arr[N];
	};


	template <typename T>
	auto& arr_at(const Vector<T>& vec, br::index_t i) {
		return vec.buffer[i];
	}


	// todo:
	// - arr_create  : create vector
	// - arr_destroy : destroy vector
	// - arr_size    : return the number of elements in vector
	// - arr_eq      : compare 2 vectors

	// other:
	// iterators  : come up with a decent interface for iterators
	// allocators : come up with a decent interface for allocators
}

#endif

