#pragma once
#ifndef BEDROCK_CHAR_HPP
#define BEDROCK_CHAR_HPP

// ...

#include "type.hpp"

namespace br {
	// Find byte size of UTF-8 character.
	constexpr u8 utf8_char_size(const char* c) {
		const bool vals[] = {
			(*c & 0b10000000) == 0b00000000,
			(*c & 0b11100000) == 0b11000000,
			(*c & 0b11110000) == 0b11100000,
			(*c & 0b11111000) == 0b11110000,
		};

		u8 out = 0;

		for (int i = 0; i < 4; ++i)
			vals[i] && (out = i);

		return out + 1;
	}


	constexpr bool is_whitespace(const char* c) {
		i32 chr = *static_cast<const i32*>(static_cast<const void*>(c));

		return
			(chr >= 0x0009 && chr <= 0x000D)
			or chr == 0x0020
			or chr == 0x0085
			or chr == 0x00A0
			or chr == 0x1680
			or (chr >= 0x2000 && chr <= 0x200A)
			or chr == 0x2028
			or chr == 0x2029
			or chr == 0x202F
			or chr == 0x205F
			or chr == 0x3000
		;
	}


	// constexpr bool is_digit(const char* c) {
	// 	return
	// }

	// todo
	// - is_digit
	// - is_lower
	// - is_upper
	// - is_alpha
	// - is_alphanumeric
}

#endif


