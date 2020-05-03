cmake_minimum_required(VERSION 3.14)

project(ImGuiFileDialog CXX)

set(IGFD_CORE_PATH ${PROJECT_SOURCE_DIR})

set(IGFD_SOURCES
    ${IGFD_CORE_PATH}/ImGuiFileDialog.cpp
    ${IGFD_CORE_PATH}/ImGuiFileDialog.hpp
    ${IGFD_CORE_PATH}/ImGuiFileDialogIcons.cpp
    ${IGFD_CORE_PATH}/ImGuiFileDialogIcons.hpp
)

add_library(ImGuiFileDialog STATIC ${IGFD_SOURCES})

include(LinkLibraries)
target_link_libraries_sys_private(ImGuiFileDialog
    CONAN_PKG::glad
    glfw
    ImGui
)

if (WIN32)
    target_link_libraries_sys_private(ImGuiFileDialog
        CONAN_PKG::dirent
    )
endif (WIN32)

target_include_directories(ImGuiFileDialog PUBLIC ${IGFD_CORE_PATH})