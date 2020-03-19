cmake_minimum_required(VERSION 3.14)

project(Xenon CXX)

# configure Conan
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()

conan_basic_setup()

# configure CMake module path and include macros
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(MacroLibrary)

# require out-of-source builds
ENSURE_OUT_OF_SOURCE_BUILD(
    "You cannot build in a source directory (or any directory with a CMakeLists.txt file).\
     Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles."
)

# general configuration
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(XENON_STANDALONE TRUE)
endif()

option(XENON_BUILD_SHARED "Build Xenon as a shared library" ON)
option(XENON_BUILD_EXAMPLES "Build the Xenon example programs" ${XENON_STANDALONE})
# option(XENON_BUILD_TESTS "Build the Xenon test programs" ${XENON_STANDALONE})

# enable project folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# set up our directory structure for output libraries and binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# compiler config
if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

# add src
add_subdirectory(src)

# add sample executables
if (XENON_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()