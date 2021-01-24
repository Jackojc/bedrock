#pragma once
#ifndef BEDROCK_ALGORITHMS_HPP
#define BEDROCK_ALGORITHMS_HPP

// ...

#include "../core/type.hpp"
#include "../core/trait.hpp"

namespace br {
	// timsort
	// find
	// map function
	// sum function
	// all/any functions



	template <typename T>
	constexpr auto copy(const Range<T>& r, T& dest) noexcept {
		static_assert(is_iterator_v<T>, "T is not an iterator.");

		auto [start, end] = r;

		while (start != end)
			*dest++ = *start++;

		return dest;
	}


	template <typename T>
	constexpr auto copy_n(T& start, const br::index_t n, T& dest) noexcept {
		static_assert(is_iterator_v<T>, "T is not an iterator.");

		for (br::index_t i = 0; i != n; ++i)
			*dest++ = *start++;

		return dest;
	}


	template <typename T, typename V>
	constexpr void fill(Container<T>& c, const V& value) noexcept {
		auto start = br::begin(c);
		auto end = br::end(c);

		while (start != end)
			*start++ = value;
	}
}

#endif

