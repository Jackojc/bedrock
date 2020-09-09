#pragma once
#ifndef BEDROCK_MEMORY_HPP
#define BEDROCK_MEMORY_HPP

// Common memory-related functions.

#include "types.hpp"
#include "traits.hpp"

namespace br {


	template <typename T>
	constexpr auto copy(T& start, const T& end, T& dest) noexcept {
		static_assert(is_iterator<T>, "T is not an iterator.");

		while (start != end) {
			*dest = *start;
			br::next(start, dest);
		}

		return dest;
	}


	template <typename T>
	constexpr auto copy_n(T& start, const br::index_t n, T& dest) noexcept {
		static_assert(is_iterator<T>, "T is not an iterator.");

		for (br::index_t i = 0; i != n; ++i) {
			*dest = *start;
			br::next(start, dest);
		}

		return dest;
	}


	template <typename T, typename V>
	constexpr void fill(T& start, const T& end, const V& value) noexcept {
		while (start != end) {
			*start = value;
			br::next(start);
		}
	}
}

#endif

