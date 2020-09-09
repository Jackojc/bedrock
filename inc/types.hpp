#pragma once
#ifndef BEDROCK_TYPES_HPP
#define BEDROCK_TYPES_HPP

// Type aliases.

namespace br {
	using u8 = unsigned char;
	using i8 = signed char;

	using u16 = unsigned short;
	using i16 = signed short;

	using u32 = unsigned long;
	using i32 = signed long;

	using u64 = unsigned long long;
	using i64 = signed long long;

	using size_t = u64;
	using index_t = u64;

	using f32 = float;
	using f64 = double;
	using f128 = long double;

	using byte = u8;
}

#endif


