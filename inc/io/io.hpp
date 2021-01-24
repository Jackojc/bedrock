#pragma once
#ifndef BEDROCK_IO_HPP
#define BEDROCK_IO_HPP

// ...

#include <cstdio>

namespace br {
	// struct File {};
	// struct Printer {};


	// Printer& operator()(Printer& p, int i) {

	// }


	template <typename T1, typename... Ts>
	inline void print(const T1& first, const Ts&... rest) noexcept {
		print(first);
		(print(rest), ...);
	}


	// inline void printer(char c) {
	// 	std::putc(c, stdout);
	// }

	// inline void printer(const char* str) {
	// 	while (*str != '\0')
	// 		printer(*str++);
	// }



	// todo:
	// - custom printf
	// - colour support
	// - logging
	// - lexical cast : convert strings to ints, floats etc
	// - format function like c++20 format
	// - print functions for primitive types and container types

	// other:
	// - support using user provided buffer
	// - define interface for printing objects
}

#endif

