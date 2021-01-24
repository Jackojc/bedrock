#pragma once
#ifndef BEDROCK_ARRAY_HPP
#define BEDROCK_ARRAY_HPP

// A wrapper around C-style arrays which doesn't decay to a pointer.

#include "../core/type.hpp"
#include "../core/trait.hpp"
#include "../algorithms/algorithm.hpp"

namespace br {
	// Iterator.
	template <typename T>
	struct ArrayIterator: BiDirectionalIterator<ArrayIterator<T>> {
		T* ptr = nullptr;


		constexpr ArrayIterator(const T* const ptr_): ptr(ptr_) {}


		constexpr T& operator*() const {
			return *ptr;
		}

		void next() { ++ptr; }
		void prev() { --ptr; }

		constexpr ArrayIterator<T>& operator++() noexcept {
			++ptr;
			return *this;
		}

		constexpr ArrayIterator<T> operator++(int) noexcept {
			auto tmp = *this;
			++ptr;
			return tmp;
		}

		constexpr ArrayIterator<T>& operator--() noexcept {
			--ptr;
			return *this;
		}

		constexpr ArrayIterator<T> operator--(int) noexcept {
			auto tmp = *this;
			--ptr;
			return tmp;
		}
	};


	template <typename T> constexpr bool operator==(const ArrayIterator<T>& lhs, const ArrayIterator<T>& rhs) {
		return lhs.ptr == rhs.ptr;
	}

	template <typename T> constexpr bool operator!=(const ArrayIterator<T>& lhs, const ArrayIterator<T>& rhs) {
		return lhs.ptr != rhs.ptr;
	}





	// Array.
	template <typename T, br::size_t N>
	struct Array: Container<Array<T, N>> {
		T buffer[N]{0};


		constexpr br::size_t size() const noexcept {
			return N;
		}

		constexpr T& at(br::index i) {
			return buffer[i];
		}

		constexpr const T& at(br::index i) const {
			return buffer[i];
		}


		// Obtain iterators.
		constexpr ArrayIterator<T> begin() noexcept {
			return ArrayIterator<T>{buffer};
		}

		constexpr ArrayIterator<T> end() noexcept {
			return ArrayIterator<T>{buffer + N};
		}


		constexpr const ArrayIterator<T> begin() const noexcept {
			return ArrayIterator<T>{buffer};
		}

		constexpr const ArrayIterator<T> end() const noexcept {
			return ArrayIterator<T>{buffer + N};
		}


		// Overloads.
		constexpr T& operator[](br::index_t i) noexcept {
			return buffer[i];
		}
	};


	template <typename T, typename... Ts>
	Array(T, Ts...) -> Array<T, 1 + sizeof...(Ts)>;




	template <typename T, typename... Ts>
	constexpr auto arr_create(const T& first, const Ts&... elements) {
		ensure_variadic_parity<T, Ts...>();

		T tmp[] = { first, elements... };
		Array<T, sizeof...(Ts) + 1> arr;

		for (br::index_t i = 0; i < sizeof...(Ts) + 1; i++)
			arr.buffer[i] = tmp[i];

		return arr;
	}

	template <typename T, br::size_t N>
	constexpr auto arr_create() {
		return br::Array<T, N>{};
	}



	template <typename T, br::size_t N>
	constexpr ArrayIterator<T>& at(const Array<T, N>& arr, br::index_t i) {
		return arr.buffer[i];
	}

	template <typename T, br::size_t N>
	constexpr const ArrayIterator<T>& at(const Array<T, N>& arr, br::index_t i) {
		return arr.buffer[i];
	}

	template <typename T, br::size_t N>
	constexpr br::size_t size(const Array<T, N>&) {
		return N;
	}

	template <typename T, br::size_t N>
	constexpr bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
		bool same = true;

		for (br::index_t i = 0; i < N; ++i)
			same = lhs[i] == rhs[i];

		return same;
	}

	template <typename T, br::size_t N>
	constexpr bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
		return not(lhs == rhs);
	}





	// other:
	// iterators  : come up with a decent interface for iterators
	// allocators : come up with a decent interface for allocators
}

#endif

