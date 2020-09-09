#pragma once
#ifndef BEDROCK_LIMITS_HPP
#define BEDROCK_LIMITS_HPP

// Numeric limits for fundamental types.

#include <climits>
#include <cfloat>

#include "types.hpp"

namespace br::limits {
	template <typename T> T max();
	template <typename T> T min();


	// 8
	template <> br::u8 max<br::u8>() { return UCHAR_MAX; }
	template <> br::i8 max<br::i8>() { return SCHAR_MIN; }

	template <> br::u8 min<br::u8>() { return 0; }
	template <> br::i8 min<br::i8>() { return SCHAR_MIN; }


	// 16
	template <> br::u16 max<br::u16>() { return USHRT_MAX; }
	template <> br::i16 max<br::i16>() { return SHRT_MAX; }

	template <> br::u16 min<br::u16>() { return 0; }
	template <> br::i16 min<br::i16>() { return SHRT_MIN; }


	// 32
	template <> br::u32 max<br::u32>() { return UINT_MAX; }
	template <> br::i32 max<br::i32>() { return INT_MAX; }

	template <> br::u32 min<br::u32>() { return 0; }
	template <> br::i32 min<br::i32>() { return INT_MIN; }

	template <> br::f32 max<br::f32>() { return FLT_MAX; }
	template <> br::f32 min<br::f32>() { return FLT_TRUE_MIN; }


	// 64
	template <> br::u64 max<br::u64>() { return ULLONG_MAX; }
	template <> br::i64 max<br::i64>() { return LLONG_MAX; }

	template <> br::u64 min<br::u64>() { return 0; }
	template <> br::i64 min<br::i64>() { return LLONG_MIN; }

	template <> br::f64 max<br::f64>() { return DBL_MAX; }
	template <> br::f64 min<br::f64>() { return DBL_TRUE_MIN; }


	// 128
	template <> br::f128 max<br::f128>() { return LDBL_MAX; }
	template <> br::f128 min<br::f128>() { return LDBL_TRUE_MIN; }
}

#endif



