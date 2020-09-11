#pragma once
#ifndef BEDROCK_STRING_HPP
#define BEDROCK_STRING_HPP

// A UTF-8 string type.

#include "trait.hpp"

namespace br {
	// todo: implement a UTF-8 string type.
	struct String: Container<String> {

	};


	// todo
	// - str_create
	// - str_destroy
	// - str_size    : character size, not byte size
	// - str_bytes   : byte size, ignoring multi-byte utf chars
	// - str_cat     : append another string
	// - str_eq      : compare 2 strings
}

#endif

