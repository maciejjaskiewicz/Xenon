project(CustomMain)

set (CUSTOM_MAIN_SOURCES
    src/CustomMain.cpp
)

add_executable(CustomMain ${CUSTOM_MAIN_SOURCES})
target_link_libraries(CustomMain Xenon::Engine)

set_target_properties(CustomMain PROPERTIES FOLDER Examples)

# disable PDBs warning for MSVC
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(CustomMain PROPERTIES LINK_FLAGS "/ignore:4099")
endif()