set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(Core)
add_subdirectory(Config)
add_subdirectory(Utils)
add_subdirectory(Services)
add_subdirectory(Platform)
add_subdirectory(Graphics)

set (XN_INCLUDES
    ${XN_INCROOT}/Core.hpp
    ${XN_INCROOT}/Config.hpp
    ${XN_INCROOT}/Xenon.hpp
    ${XN_INCROOT}/Utils.hpp
    ${XN_INCROOT}/Services.hpp
    ${XN_INCROOT}/Graphics.hpp
)

set (XN_SOURCES
    ${XN_SOURCES_CORE}
    ${XN_SOURCES_CONFIG}
    ${XN_SOURCES_UTILS}
    ${XN_SOURCES_SERVICES}
    ${XN_SOURCES_PLATFORM}
    ${XN_SOURCES_GRAPHICS}
)

source_group("" FILES ${XN_INCLUDES})
source_group("Core" FILES ${XN_SOURCES_CORE_ROOT})
source_group("Core\\Window" FILES ${XN_SOURCES_CORE_WINDOW})
source_group("Core\\Events" FILES ${XN_SOURCES_CORE_EVENTS})
source_group("Core\\Input" FILES ${XN_SOURCES_CORE_INPUT})
source_group("Core\\Gui" FILES ${XN_SOURCES_CORE_GUI})
source_group("Config" FILES ${XN_SOURCES_CONFIG})
source_group("Utils" FILES ${XN_SOURCES_UTILS})
source_group("Services\\Log" FILES ${XN_SOURCES_SERVICES_LOG})
source_group("Services\\Event" FILES ${XN_SOURCES_SERVICES_EVENT})
source_group("Platform\\GLFW" FILES ${XN_SOURCES_PLATFORM_GLFW})
source_group("Platform\\OpenGL" FILES ${XN_SOURCES_PLATFORM_OPENGL})
source_group("Graphics" FILES ${XN_SOURCES_GRAPHICS})

# create library
add_library(Xenon STATIC ${XN_INCLUDES} ${XN_SOURCES})
add_library(Xenon::Engine ALIAS Xenon)

# link third party libraries
find_package(OpenGL REQUIRED)

target_link_libraries(Xenon OpenGL::GL)
target_link_libraries(Xenon glfw)
target_link_libraries(Xenon ImGui)
conan_target_link_libraries(Xenon)

# set include directories
target_include_directories(Xenon PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Xenon PRIVATE ${PROJECT_SOURCE_DIR}/include/Xenon)

# set extra definitions
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Xenon PUBLIC XN_MODE_DEBUG)
endif()

# disable PDBs warning for MSVC
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(Xenon PROPERTIES LINK_FLAGS "/ignore:4099")
endif()