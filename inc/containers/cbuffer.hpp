#pragma once
#ifndef BEDROCK_CBUFFER_HPP
#define BEDROCK_CBUFFER_HPP

// Circular buffer.

#include "../core/type.hpp"
#include "../core/trait.hpp"
#include "../algorithms/algorithm.hpp"

namespace br {
	// Iterator.
	template <typename T>
	struct CBufferIterator: BiDirectionalIterator<CBufferIterator<T>> {
		T* ptr = nullptr;


		constexpr T& operator*() const {
			return *ptr;
		}

		void next() { ++ptr; }
		void prev() { --ptr; }

		constexpr CBufferIterator<T>& operator++() noexcept {
			++ptr;
			return *this;
		}

		constexpr CBufferIterator<T> operator++(int) noexcept {
			auto tmp = *this;
			++ptr;
			return tmp;
		}

		constexpr CBufferIterator<T>& operator--() noexcept {
			--ptr;
			return *this;
		}

		constexpr CBufferIterator<T> operator--(int) noexcept {
			auto tmp = *this;
			--ptr;
			return tmp;
		}
	};


	template <typename T> constexpr bool operator==(const CBufferIterator<T>& lhs, const CBufferIterator<T>& rhs) {
		return lhs.ptr == rhs.ptr;
	}

	template <typename T> constexpr bool operator!=(const CBufferIterator<T>& lhs, const CBufferIterator<T>& rhs) {
		return lhs.ptr != rhs.ptr;
	}





	// CBuffer.
	template <typename T, br::size_t N>
	struct CBuffer: Container<CBuffer<T, N>> {
		T buffer[N]{0};

		// Obtain iterators.
		constexpr auto begin() noexcept {
			CBufferIterator<T> it;
			it.ptr = buffer;
			return it;
		}

		constexpr auto end() noexcept {
			CBufferIterator<T> it;
			it.ptr = buffer + N;
			return it;
		}

		constexpr T& operator[](br::index_t i) noexcept {
			return buffer[i];
		}
	};


	template <typename T, typename... Ts>
	constexpr auto cbuf_create(const T& first, const Ts&... elements) {
		ensure_variadic_parity<T, Ts...>();

		T tmp[] = { first, elements... };
		CBuffer<T, sizeof...(Ts) + 1> arr;

		for (br::index_t i = 0; i < sizeof...(Ts) + 1; i++)
			arr.buffer[i] = tmp[i];

		return arr;
	}

	template <typename T, br::size_t N>
	constexpr auto cbuf_create() {
		return br::CBuffer<T, N>{};
	}



	template <typename T, br::size_t N>
	constexpr auto& at(const CBuffer<T, N>& arr, br::index_t i) {
		return arr.buffer[i];
	}

	template <typename T, br::size_t N>
	constexpr br::size_t size(const CBuffer<T, N>&) {
		return N;
	}

	template <typename T, br::size_t N>
	constexpr bool operator==(const CBuffer<T, N>& lhs, const CBuffer<T, N>& rhs) {
		bool same = true;

		for (br::index_t i = 0; i < N; ++i)
			same = lhs[i] == rhs[i];

		return same;
	}

	template <typename T, br::size_t N>
	constexpr bool operator!=(const CBuffer<T, N>& lhs, const CBuffer<T, N>& rhs) {
		return not(lhs == rhs);
	}
}

#endif

