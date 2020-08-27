#ifndef BEDROCK_VECTOR_HPP
#define BEDROCK_VECTOR_HPP

// ...

#include <cstdlib> // realloc

#include <types.hpp>

namespace br {
	template <typename T>
	struct Vector {
		br::size_t used;   // Capacity used so far.
		br::size_t total;  // Total capacity.

		T* buffer;
	};


	namespace detail {
		template <typename T>
		void vec_grow(const Vector<T>& vec) {
			auto& [used, total, buffer] = vec;

			total *= 2;
			buffer = std::realloc(static_cast<void*>(buffer), total);
		}
	}


	template <typename T>
	auto& vec_at(const Vector<T>& vec, br::index_t i) {
		return vec.buffer[i];
	}


	template <typename T, typename V>
	auto& vec_append(const Vector<T>& vec, const V& value) {
		// append `value` and grow if needed.
	}

	// todo:
	// - vec_create  : create vector
	// - vec_destroy : destroy vector
	// - vec_size    : return the number of elements in vector
	// - vec_extend  : append a vector to another vector
	// - vec_insert  : insert element at specific index
	// - vec_remove  : remove element at specific index
	// - vec_pop     : pop last element
	// - vec_eq      : compare 2 vectors

	// other:
	// iterators  : come up with a decent interface for iterators
	// allocators : come up with a decent interface for allocators
}

#endif

