cmake_minimum_required(VERSION 3.15)

project(Xenon CXX)

# configure CMake modules and include macros
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(MacroLibrary)

# require out-of-source builds
ENSURE_OUT_OF_SOURCE_BUILD(
    "You cannot build in a source directory (or any directory with a CMakeLists.txt file).\
     Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles."
)

#include and apply Xenon settings
include(Settings)
include(StaticAnalyzers)

# general configuration
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(XENON_STANDALONE TRUE)
endif()

option(XENON_BUILD_EXAMPLES "Build the Xenon example programs" ${XENON_STANDALONE})
option(XENON_BUILD_TESTS "Build the Xenon test programs" ${XENON_STANDALONE})
option(XENON_BUILD_VEROSE "Build Xenon with Verbose mode" OFF)

# libraries with the predefined project configuration to use by clients 
add_library(XenonOptions INTERFACE)
target_compile_features(XenonOptions INTERFACE cxx_std_17)
add_library(Xenon::Options ALIAS XenonOptions)

add_library(XenonWarnings INTERFACE)
add_library(Xenon::Warnings ALIAS XenonWarnings)

# Standard Precompiled Header
include(PrecompiledHeader)
set_standard_pch(XenonOptions)

# standard compiler warnings
include(Warnings)
set_project_warnings(XenonWarnings)

# sanitizer options if supported by compiler
include(Sanitizers)
enable_sanitizers(XenonOptions)

# fetch and configure third party libraries with Conan or FetchContent 
include(Conan)
conan_cmake_run(CONANFILE conanfile.txt
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing
)

include(FetchContent)
SET(FETCHCONTENT_QUIET XENON_BUILD_VEROSE)

include(FetchGLFW)
include(FetchImGui)

# add src
add_subdirectory(src)

# add sample executables
if (XENON_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (XENON_BUILD_TESTS)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(tests)
endif()