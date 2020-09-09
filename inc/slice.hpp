#pragma once
#ifndef BEDROCK_SLICE_HPP
#define BEDROCK_SLICE_HPP

// A slice type for a lightweight "view" into a container type.

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

