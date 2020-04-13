#pragma once

#ifndef SPDLOG_FMT_EXTERNAL
    #define SPDLOG_FMT_EXTERNAL
#endif

#include "Log.hpp"

#include <string>
#include <cassert>

/*
 * Platform detection
 */

#if defined _WIN32 || defined __CYGWIN__
    #define XN_PLATFORM_WINDOWS
#elif defined(__ANDROID__)
    #define XN_PLATFORM_ANDROID
    #error Unsupported platform!
#elif defined(__linux__)
    #define XN_PLATFORM_LINUX
#else
    #error Unsupported platform!
#endif

/*
 * Debug and assertion
 */

#ifndef XN_UNUSED
    #define XN_UNUSED(x) ((void)(x));
#endif

#ifdef XN_MODE_DEBUG
	#define XN_ENABLE_ASSERTS
#endif

#ifdef _MSC_VER
    #define DEBUG_BREAK __debugbreak()
#else
    #define DEBUG_BREAK assert(false)
#endif

#ifdef XN_ENABLE_ASSERTS
    #define XN_ASSERT(x) { if(!(x)) { XN_ENG_CRITICAL("Assertion Failed"); DEBUG_BREAK; } }
    #define XN_ASSERT_COM(x, comment) { if(!(x)) { XN_ENG_CRITICAL("Assertion Failed: {}", comment); DEBUG_BREAK; } }
    #define XN_ASSERT_FMT(x, fmt, ...) { if(!(x)) { XN_ENG_CRITICAL(std::string("Assertion Failed: ") + fmt, __VA_ARGS__); DEBUG_BREAK; } }
#else
    #define XN_ASSERT(x) XN_UNUSED(x)
    #define XN_ASSERT_COM(x, comment) XN_UNUSED(x)
    #define XN_ASSERT_FMT(x, fmt, ...) XN_UNUSED(x)
#endif

/*
 * Common utils
 */

#ifndef XN_NODISCARD
    #define XN_NODISCARD [[nodiscard]]
#endif