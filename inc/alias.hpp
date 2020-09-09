#pragma once
#ifndef BEDROCK_ALIAS_HPP
#define BEDROCK_ALIAS_HPP

// Create strong aliases.
// example:
//   template <typename T>
//   using MyVector = br::alias<std::vector<T>>;

namespace br {
	template <typename T>
	class alias: public T {
		public: using T::T;
	};


	// todo: implement aliases for primitive types.
}

#endif

