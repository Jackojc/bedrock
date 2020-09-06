#ifndef BEDROCK_UTIL_HPP
#define BEDROCK_UTIL_HPP

// Common functions.

#include <cstdio>
#include <cstdlib>

#include "def.hpp"

namespace br {
	// exit
	// unreachable macro
	// forward function
	// sort : timsort algorithm
	// map function
	// sum function
	// all/any functions


	template <typename... Ts>
	[[noreturn]] void halt(Ts&... args) {
		(std::fputs(args, stderr), ...);

		if constexpr(sizeof...(Ts) > 0)
			std::fputs("\n", stderr);

		std::exit(br::codes::FAILURE);
	}


	template <typename A, typename B>
	struct Pair {
		A a;
		B b;
	};


	template <typename T> constexpr void swap(T& a, T& b) {
		T tmp = a;
		a = b;
		b = tmp;
	}


	template <typename T> constexpr auto min(const T& a, const T& b) {
		return (a < b ? a : b);
	}


	template <typename T> constexpr auto max(const T& a, const T& b) {
		return (a > b ? a : b);
	}


	template <typename T> constexpr size_t ptrdiff(T* a, T* b) {
		return max(a, b) - min(a, b);
	}


}

#endif

