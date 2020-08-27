#ifndef BEDROCK_SLICE_HPP
#define BEDROCK_SLICE_HPP

// ...

#include "types.hpp"

namespace br {
	template <typename T>
	struct Slice {
		T* ptr;
		br::size_t length;
	};

	// todo
	// - design an interface for container types to return a slice
}

#endif

