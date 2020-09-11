#pragma once
#ifndef BEDROCK_STRING_HPP
#define BEDROCK_STRING_HPP

// A UTF-8 string type.

#include "type.hpp"
#include "trait.hpp"

namespace br {
	struct StringIterator: BiDirectionalIterator<StringIterator> {
		char* ptr = nullptr;

		constexpr auto& operator*() const {
			return *ptr;
		}

		void next() { ++ptr; }
		void prev() { --ptr; }

		constexpr auto& operator++() noexcept {
			++ptr;
			return *this;
		}

		constexpr auto operator++(int) noexcept {
			auto tmp = *this;
			++ptr;
			return tmp;
		}

		constexpr auto& operator--() noexcept {
			--ptr;
			return *this;
		}

		constexpr auto operator--(int) noexcept {
			auto tmp = *this;
			--ptr;
			return tmp;
		}
	};


	template <typename T> constexpr bool operator==(const StringIterator& lhs, const StringIterator& rhs) {
		return lhs.ptr == rhs.ptr;
	}

	template <typename T> constexpr bool operator!=(const StringIterator& lhs, const StringIterator& rhs) {
		return lhs.ptr != rhs.ptr;
	}





	struct String: Container<String> {
		char* buffer = nullptr;
		br::size_t char_size = 0;
		br::size_t buffer_size = 0;


		constexpr auto begin() {
			StringIterator it;
			it.ptr = buffer;
			return it;
		}

		constexpr auto end() {
			StringIterator it;
			it.ptr = buffer + buffer_size;
			return it;
		}

		// todo: make this character index, not byte index.
		constexpr const char* operator[](br::index_t i) noexcept {
			return buffer + i;
		}
	};




	constexpr String str_create() {
		return {};
	}


	template <typename T>
	constexpr String str_create(Allocator<T>& alloc, const char* str) {
		String ss;

		br::size_t sz = 0;
		while (*str++ != '\0')
			++sz;

		auto buffer = br::allocate(alloc, sz);

		for (br::index_t i = 0; i < sz; ++i)
			buffer[i] = str[i];

		ss.buffer = buffer;
		ss.char_size = utf8_char_size(buffer);
		ss.buffer_size = sz;

		return ss;
	}

	template <typename T>
	constexpr void str_destroy(Allocator<T>& alloc, String& str) {
		auto& [buffer, cs, bs] = str;
		br::release(alloc, buffer);
		cs = 0;
		bs = 0;
		buffer = nullptr;
	}



	constexpr br::size_t size(const String& str) noexcept {
		return str.char_size;
	}

	constexpr br::size_t bytes(const String& str) noexcept {
		return str.buffer_size;
	}




	constexpr bool operator==(const String& lhs, const String& rhs) {
		bool same = true;
		auto sz = bytes(lhs);

		if (sz != bytes(rhs))
			return false;

		for (br::index_t i = 0; i < sz; ++i)
			same = lhs.buffer[i] == rhs.buffer[i];

		return same;
	}

	constexpr bool operator!=(const String& lhs, const String& rhs) {
		return not(lhs == rhs);
	}



	// todo
	// - str_cat     : append another string
}

#endif

