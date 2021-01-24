#pragma once
#ifndef BEDROCK_EXIT_HPP
#define BEDROCK_EXIT_HPP

// Exit & Abort related functions.
// TODO: Implement platform specific exit & abort functions for Windows.

#include <cstdio>

#include "../core/def.hpp"

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

#endif
