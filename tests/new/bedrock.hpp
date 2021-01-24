#pragma once
#ifndef BEDROCK_HPP
#define BEDROCK_HPP

// ...

namespace br {
	using u8 = unsigned char;
	using i8 = signed char;

	using u16 = unsigned short;
	using i16 = signed short;

	using u32 = unsigned int;
	using i32 = signed int;

	using u64 = unsigned long long;
	using i64 = signed long long;

	using size_t = u64;
	using index_t = u64;

	using f32 = float;
	using f64 = double;
	using f128 = long double;
}

namespace br {
	// Stringify macro.
	#define BR_STR(x) BR_STR_IMPL_(x)
	#define BR_STR_IMPL_(x) #x


	// Detect platform.
	#if defined(_WIN64) || defined(_WIN32) || defined(__WINDOWS__)
		#define BR_PLATFORM_WINDOWS

	#elif defined(__linux) || defined(linux)
		#define BR_PLATFORM_LINUX

	#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NETBSD__) || defined(__OpenBSD__)
		#define BR_PLATFORM_BSD

	#elif defined(__APPLE__) || defined(macintosh) || defined(__MACH__)
		#define BR_PLATFORM_OSX

	#elif defined(__unix) || defined(unix)
		#define BR_PLATFORM_UNIX

	#else
		#define BR_PLATFORM_UNKNOWN

	#endif


	// Detect compiler.
	#if defined(__GNUC__)
		#define BR_COMPILER_GCC

	#elif defined(__INTEL_COMPILER)
		#define BR_COMPILER_INTEL

	#elif defined(__clang__)
		#define BR_COMPILER_CLANG

	#elif defined(_MSC_VER)
		#define BR_COMPILER_MSVC

	#else
		#define BR_COMPILER_UNKNOWN

	#endif
}


#if defined(BR_PLATFORM_LINUX)
	extern "C" {
		#include <sys/types.h>
		#include <unistd.h>
		#include <signal.h>
	}

#else
	#include <cstdlib>

#endif

namespace br {
	#if defined(EXIT_FAILURE) || defined(EXIT_SUCCESS)
		#undef EXIT_FAILURE
		#undef EXIT_SUCCESS
	#endif

	constexpr int EXIT_FAILURE = 1;
	constexpr int EXIT_SUCCESS = 0;

	// Linux specific functions.
	#if defined(BR_PLATFORM_LINUX)
		[[noreturn]] inline void exit(int code) noexcept {
			_exit(code);
		}

		[[noreturn]] inline void abort() noexcept {
			kill(getpid(), SIGABRT);

			#if defined(BR_COMPILER_GCC) || defined(BR_COMPILER_CLANG)
				__builtin_trap();
			#endif
		}

	// Fallback to C standard library.
	#else
		[[noreturn]] inline void exit(int code) noexcept {
			std::exit(code);
		}

		[[noreturn]] inline void abort() noexcept {
			std::abort();
		}

	#endif


	// Exit with a message.
	template <typename... Ts>
	[[noreturn]] void halt(Ts&... args) noexcept {
		(std::fputs(args, stderr), ...);

		if constexpr(sizeof...(Ts) > 0)
			std::fputs("\n", stderr);

		br::exit(EXIT_FAILURE);
	}
}



namespace br {
	// . argument parser

	// . memset
	// . memcpy

	// . abort
	// . exit

	// . assert
	// . static_assert

	// . time
	// . timediff

	// . file_read  -> load a file into a character buffer
	// . file_write -> write a character buffer to a new file

	// . is_alpha
	// . is_digit
	// . is_whitespace
	// . is_alphanumeric
	// . is_upper
	// . is_lower

	// . sort
	// . search

	// . print
	// . println
	// . err
	// . errln
	// . log
	// . logln


	// struct block {
	// 	void* buffer;
	// 	void* next;
	// 	size_t capacity;
	// };

	// struct pool {

	// };

	// pool pool_create(size_t bytes) {
	// 	pool p;
	// 	auto& [buffer, next, capacity] = p;

	// 	buffer = std::malloc(bytes);

	// 	for (index_t i = 0; i < bytes; ++i)
	// 		static_cast<char*>(buffer)[i] = 0;

	// 	next = buffer;
	// 	capacity = bytes;

	// 	return p;
	// }

	// void pool_destroy(pool& p) {
	// 	auto& [buffer, next, capacity] = p;

	// 	std::free(buffer);

	// 	buffer = nullptr;
	// 	next = nullptr;
	// 	capacity = 0;
	// }

	// void pool_grow(pool& p) {
	// 	auto& [buffer, next, capacity] = p;

	// 	buffer = std::realloc();
	// }

	// template <typename T>
	// T* pool_allocate(pool& p, size_t n = 1) {
	// 	T* slot = static_cast<T*>(p.next);
	// 	p.next += sizeof(T) * n;
	// 	return slot;
	// }

	// . pool_create
	// . pool_destroy
	// . pool_allocate
	// . pool_free
	// . pool_compact -> move regions around to remove gaps
	// . pool_grow    -> double the capacity of the pool


	struct alignas(alignof(br::size_t) arr_header {
		br::size_t size;
	};


	template <typename T>
	T* arr_create(br::size_t n) {
		void* buffer = std::malloc(sizeof(arr_header) + (sizeof(T) * n));

		auto header = static_cast<arr_header*>(buffer);
		header->size = n;

		return static_cast<T*>(static_cast<char*>(buffer) + sizeof(arr_header));
	}

	template <typename T>
	void arr_destroy(T* arr) {
		auto header = static_cast<char*>(arr) - sizeof(arr_header);
		std::free(static_cast<void*>(header));
	}

	template <typename T>
	br::size_t arr_size(T* arr) {
		auto header = static_cast<arr_header*>(static_cast<void*>(static_cast<char*>(arr) - sizeof(arr_header)));
		return header->size;
	}

	// . arr_size
	// . arr_at
	// . arr_dup
	// . arr_cmp

	// . vec_create
	// . vec_destroy
	// . vec_size
	// . vec_at
	// . vec_append -> add value to end of vector
	// . vec_extend -> add all elements of another vector to the end of a vector
	// . vec_insert
	// . vec_remove
	// . vec_dup
	// . vec_cmp

	// . str_create
	// . str_destroy
	// . str_chars
	// . str_bytes
	// . str_at
	// . str_cat
	// . str_validate -> validate that a string is well formed utf-8
	// . str_dup
	// . str_cmp



}

#endif
