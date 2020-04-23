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

set_custom_output(Sandbox)
set_target_properties(Sandbox PROPERTIES FOLDER Examples)

add_custom_command(TARGET Sandbox PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets/
    $<TARGET_FILE_DIR:Sandbox>/assets/
)

if(NOT $<TARGET_FILE_DIR:Sandbox> STREQUAL ${PROJECT_BINARY_DIR})
    add_custom_command(TARGET Sandbox PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets/
        ${PROJECT_BINARY_DIR}/assets/
    )
endif()