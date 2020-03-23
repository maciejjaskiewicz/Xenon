set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(Core)
add_subdirectory(Utils)
add_subdirectory(Services)

set (XN_INCLUDES
    ${XN_INCROOT}/Core.hpp
    ${XN_INCROOT}/Xenon.hpp
    ${XN_INCROOT}/Utils.hpp
    ${XN_INCROOT}/Services.hpp
)

set (XN_SOURCES
    ${XN_SOURCES_CORE}
    ${XN_SOURCES_UTILS}
    ${XN_SOURCES_SERVICES}
)

source_group("" FILES ${XN_INCLUDES})
source_group("Core" FILES ${XN_SOURCES_CORE})
source_group("Utils" FILES ${XN_SOURCES_UTILS})
source_group("Services\\Log" FILES ${XN_SOURCES_SERVICES_LOG})

# create library
if (XENON_BUILD_SHARED)
    add_library(Xenon SHARED ${XN_INCLUDES} ${XN_SOURCES})
    target_compile_definitions(Xenon PUBLIC XN_BUILD_SHARED)
    target_compile_definitions(Xenon PRIVATE XN_SHARED_EXPORTS)
else()
    add_library(Xenon STATIC ${XN_INCLUDES} ${XN_SOURCES})
endif()

add_library(Xenon::Engine ALIAS Xenon)

# link third party libraries
conan_target_link_libraries(Xenon)

# set include directories
target_include_directories(Xenon PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Xenon PRIVATE ${PROJECT_SOURCE_DIR}/include/Xenon)

# set extra definitions
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Xenon PUBLIC XN_DEBUG)
endif()

# disable PDBs warning for MSVC
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(Xenon PROPERTIES LINK_FLAGS "/ignore:4099")
endif()