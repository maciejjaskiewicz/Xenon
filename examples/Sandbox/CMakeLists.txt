project(Sandbox)

set (SANDBOX_SOURCES
    src/Sandbox.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})
target_link_libraries(Sandbox PRIVATE
    Xenon::Options
    Xenon::Warnings
    Xenon::Engine
)

set_target_properties(Sandbox PROPERTIES FOLDER Examples)