#pragma once
#ifndef BEDROCK_DEF_HPP
#define BEDROCK_DEF_HPP

// Common definitions.

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

#endif
