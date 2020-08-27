#ifndef BEDROCK_DEF_HPP
#define BEDROCK_DEF_HPP

// Common definitions.

namespace br {
	#undef EXIT_FAILURE
	#undef EXIT_SUCCESS

	// todo: consult unix spec for error numbers
	constexpr int EXIT_SUCCESS = 0;
	constexpr int EXIT_FAILURE = 1;
}

#endif
