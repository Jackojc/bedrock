#pragma once
#ifndef BEDROCK_EXIT_HPP
#define BEDROCK_EXIT_HPP

// ...

#include <cstdio>

#include "def.hpp"

#ifdef BR_PLATFORM_LINUX
	extern "C" {
		#include <sys/types.h>
		#include <unistd.h>
		#include <signal.h>
	}
#endif

namespace br {
	#if defined(EXIT_FAILURE) || defined(EXIT_SUCCESS)
		#undef EXIT_FAILURE
		#undef EXIT_SUCCESS
	#endif

	constexpr int EXIT_FAILURE = 1;
	constexpr int EXIT_SUCCESS = 0;

	#if defined(BR_PLATFORM_LINUX) || defined(BR_PLATFORM_UNIX)
		[[noreturn]] inline void exit(int code) noexcept {
			_exit(code);
		}

		#if defined(BR_COMPILER_GCC) || defined(BR_COMPILER_CLANG)
			[[noreturn]] inline void abort() noexcept {
				__builtin_trap();
			}
		#else
			inline void abort() noexcept {
				kill(getpid(), SIGABRT);
			}
		#endif

	#else
		#error UNIMPLEMENTED

	#endif

	template <typename... Ts>
	[[noreturn]] void halt(Ts&... args) noexcept {
		(std::fputs(args, stderr), ...);

		if constexpr(sizeof...(Ts) > 0)
			std::fputs("\n", stderr);

		br::exit(EXIT_FAILURE);
	}
}

#endif
