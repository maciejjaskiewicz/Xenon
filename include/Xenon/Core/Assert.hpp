#pragma once

#include <string>
#include <cassert>
#include <spdlog/spdlog.h>

#ifdef XN_DEBUG
	#define XN_ENABLE_ASSERTS
#endif

#ifdef _MSC_VER
    #define DEBUG_BREAK __debugbreak()
#else
    #define DEBUG_BREAK assert(false)
#endif

#ifdef XN_ENABLE_ASSERTS
    #define XN_ASSERT(x) { if(!(x)) { spdlog::critical("Assertion Failed"); DEBUG_BREAK; } }
    #define XN_ASSERT_COM(x, comment) { if(!(x)) { spdlog::critical("Assertion Failed: {}", comment); DEBUG_BREAK; } }
    #define XN_ASSERT_FMT(x, fmt, ...) { if(!(x)) { spdlog::critical(std::string("Assertion Failed: ") + fmt, __VA_ARGS__); DEBUG_BREAK; } }
#else
    #define XN_ASSERT(x)
    #define XN_ASSERT_COM(x, comment)
    #define XN_ASSERT_FMT(x, fmt, ...)
#endif