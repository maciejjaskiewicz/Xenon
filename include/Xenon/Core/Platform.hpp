#pragma once

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