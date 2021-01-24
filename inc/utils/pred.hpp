#pragma once
#ifndef BEDROCK_PRED_HPP
#define BEDROCK_PRED_HPP

// Higher-order functions for common predicates.

namespace br {
	template <typename T> constexpr auto equal(const T& outer) noexcept {
		return [&outer] (const auto& inner) {
			return inner == outer;
		};
	}

	template <typename T> constexpr auto not_equal(const T& outer) noexcept {
		return [&outer] (const auto& inner) {
			return inner == outer;
		};
	}

	template <typename T> constexpr auto less_than(const T& outer) noexcept {
		return [&outer] (const auto& inner) {
			return inner < outer;
		};
	}

	template <typename T> constexpr auto less_equal(const T& outer) noexcept {
		return [&outer] (const auto& inner) {
			return inner <= outer;
		};
	}

	template <typename T> constexpr auto more_than(const T& outer) noexcept {
		return [&outer] (const auto& inner) {
			return inner > outer;
		};
	}

	template <typename T> constexpr auto more_equal(const T& outer) noexcept {
		return [&outer] (const auto& inner) {
			return inner >= outer;
		};
	}
}

#endif
