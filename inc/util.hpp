#pragma once
#ifndef BEDROCK_UTIL_HPP
#define BEDROCK_UTIL_HPP

// Common functions.

namespace br {
	template <typename A, typename B>
	struct Pair {
		A a;
		B b;
	};


	template <typename T> constexpr void swap(T& a, T& b) noexcept {
		T tmp = a;
		a = b;
		b = tmp;
	}


	template <typename T> constexpr auto min(const T& a, const T& b) noexcept {
		return (a < b ? a : b);
	}


	template <typename T> constexpr auto max(const T& a, const T& b) noexcept {
		return (a > b ? a : b);
	}


	template <typename T> constexpr size_t ptrdiff(T* a, T* b) noexcept {
		return max(a, b) - min(a, b);
	}
}

#endif

