project(Sandbox)

set (SANDBOX_SOURCES
    src/Sandbox.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})
target_link_libraries(Sandbox Xenon::Engine)

set_target_properties(Sandbox PROPERTIES FOLDER Examples)

# disable PDBs warning for MSVC
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(Sandbox PROPERTIES LINK_FLAGS "/ignore:4099")
endif()