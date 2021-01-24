#pragma once
#ifndef BEDROCK_ASSERT_HPP
#define BEDROCK_ASSERT_HPP

// Assertion macros.
//
// BR_ENABLE_ASSERT  => Enable assertions even when NDEBUG is set.
// BR_DISABLE_ASSERT => Disable assertions explicitly.

#include <cstdio>

#include "def.hpp"
#include "exit.hpp"

namespace br {
	// todo
	// maybe add some pretty colours too and line/file info


	#ifdef NDEBUG
		#ifndef BR_ENABLE_ASSERT
			#define BR_DISABLE_ASSERT
		#endif
	#endif


	#ifndef BR_DISABLE_ASSERT
		#define BR_UNREACHABLE() \
			do { \
				br::halt("[", __FILE__, ":", BR_STR(__LINE__), "] unreachable code!"); \
			} while (0)

		#define BR_ASSERT(cond, msg) \
			do { \
				if (not (cond)) \
					br::halt("[", __FILE__, ":", BR_STR(__LINE__), "] assert '", BR_STR(cond), "' failed with '", msg, "'!"); \
			} while (0)

		#define BR_STATIC_ASSERT(cond, msg) \
			do { \
				static_assert(cond, "[" __FILE__ ":" BR_STR(__LINE__) "] assert '" #cond "' failed with '" msg "'!\n"); \
			} while (0)

	#else
		#define BR_UNREACHABLE() do {} while (0)
		#define BR_ASSERT(cond, msg) do {} while (0)
		#define BR_STATIC_ASSERT(cond, msg) do {} while (0)

	#endif
}

#endif


