set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src)

set (XN_INCLUDES
    ${XN_INCROOT}/Core.hpp
    ${XN_INCROOT}/Xenon.hpp
)

set (XN_CORE
    ${XN_INCROOT}/Core/Api.hpp
    ${XN_SRCROOT}/Core/Application.cpp
    ${XN_INCROOT}/Core/Application.hpp
    ${XN_INCROOT}/Core/Platform.hpp
)

source_group("" FILES ${XN_INCLUDES})
source_group("Core" FILES ${XN_CORE})

# create library
if (XENON_BUILD_SHARED)
    add_library(Xenon SHARED ${XN_INCLUDES} ${XN_CORE})
    target_compile_definitions(Xenon PUBLIC XN_BUILD_SHARED)
    target_compile_definitions(Xenon PRIVATE XN_SHARED_EXPORTS)
else()
    add_library(Xenon STATIC ${XN_INCLUDES} ${XN_CORE})
endif()

add_library(Xenon::Engine ALIAS Xenon)

# link third party libraries
conan_target_link_libraries(Xenon)

# set include directories
target_include_directories(Xenon PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Xenon PRIVATE ${PROJECT_SOURCE_DIR}/include/Xenon)

# disable PDBs warning for MSVC
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(Xenon PROPERTIES LINK_FLAGS "/ignore:4099")
endif()