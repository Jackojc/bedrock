#ifndef BEDROCK_ASSERT_HPP
#define BEDROCK_ASSERT_HPP

// Assertion macros.
//
// BR_ENABLE_ASSERT  => Enable assertions even when NDEBUG is set.
// BR_DISABLE_ASSERT => Disable assertions explicitly.

#include <cstdio>

#include "def.hpp"
#include "io.hpp"

namespace br {
	// todo
	// assert macros with the ability to be disabled
	// maybe add some pretty colours too and line/file info
	// compile time and runtime asserts


	#ifdef NDEBUG
		#ifndef BR_ENABLE_ASSERT
			#define BR_DISABLE_ASSERT
		#endif
	#endif


	#ifndef BR_DISABLE_ASSERT
		#define BR_RUNTIME_ASSERT(cond, msg) \
			do { \
				if (not (cond)) \
					std::fprintf(stderr, "[%s:%d] assert '%s' failed with '%s'!\n", __FILE__, __LINE__, #cond, msg); \
					br::halt(); \
			} while (0)

		#define BR_COMPILETIME_ASSERT(cond, msg) \
			do { \
				static_assert(cond, "[" __FILE__ ":" STR(__LINE__) "] assert '" #cond "' failed with '" msg "'!\n"); \
			} while (0)

	#else
		#define BR_RUNTIME_ASSERT(cond, msg) do {} while (0)
		#define BR_COMPILETIME_ASSERT(cond, msg) do {} while (0)

	#endif
}

#endif


