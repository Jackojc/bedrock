#pragma once
#ifndef BEDROCK_HETERO_VECTOR_HPP
#define BEDROCK_HETERO_VECTOR_HPP

// Heterogenous vector.

#include <cstdlib> // realloc

#include "type.hpp"
#include "trait.hpp"

namespace br {
	template <typename T>
	struct HVector: Container<HVector<T>> {
		br::size_t used;   // Capacity used so far.
		br::size_t total;  // Total capacity.

		T* buffer;
	};


	namespace detail {
		template <typename T>
		void vec_grow(const HVector<T>& vec) {
			auto& [used, total, buffer] = vec;

			total *= 2;
			buffer = std::realloc(static_cast<void*>(buffer), total);
		}
	}


	template <typename T>
	auto& vec_at(const HVector<T>& vec, br::index_t i) {
		return vec.buffer[i];
	}


	template <typename T, typename V>
	auto& vec_append(const HVector<T>& vec, const V& value) {
		// append `value` and grow if needed.
	}
}

#endif

