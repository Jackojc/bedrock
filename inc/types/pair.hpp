#pragma once
#ifndef BEDROCK_PAIR_HPP
#define BEDROCK_PAIR_HPP

// Pair.

namespace br {
	template <typename A, typename B>
	struct Pair {
		A a {};
		B b {};

		constexpr Pair(A&& a_, B&& b_): a(a_), b(b_) {}
		constexpr Pair() {}
	};

	template <typename A, typename B>
	Pair(A a, B b) -> Pair<A, B>;
}

#endif

