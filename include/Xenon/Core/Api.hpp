#pragma once

/*
 * Generic helper definitions for shared library support
 */

#if defined _WIN32 || defined __CYGWIN__
    #define XN_HELPER_SHARED_IMPORT __declspec(dllimport)
    #define XN_HELPER_SHARED_EXPORT __declspec(dllexport)
    #define XN_HELPER_SHARED_LOCAL
#else
    #if __GNUC__ >= 4
        #define XN_HELPER_SHARED_IMPORT __attribute__ ((visibility ("default")))
        #define XN_HELPER_SHARED_EXPORT __attribute__ ((visibility ("default")))
        #define XN_HELPER_SHARED_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
        #define XN_HELPER_SHARED_IMPORT
        #define XN_HELPER_SHARED_EXPORT
        #define XN_HELPER_SHARED_LOCAL
    #endif
#endif

/*
 * XN_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
 * XN_LOCAL is used for non-api symbols.
 */

#ifdef XN_BUILD_SHARED // defined if Xenon is compiled as a DLL
    #ifdef XN_SHARED_EXPORTS // defined if we are building the Xenon DLL (instead of using it)
        #define XN_API XN_HELPER_SHARED_EXPORT
    #else
        #define XN_API XN_HELPER_SHARED_IMPORT
    #endif
        #define XN_LOCAL XN_HELPER_SHARED_LOCAL
#else // XN_BUILD_SHARED is not defined: this means Xenon is a static lib.
    #define XN_API
    #define XN_LOCAL
#endif