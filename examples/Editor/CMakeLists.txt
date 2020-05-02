project(Editor)

set (EDITOR_SOURCES
    src/Editor.cpp
)

add_executable(Editor ${EDITOR_SOURCES})
target_link_libraries(Editor PRIVATE
    Xenon::Options
    Xenon::Warnings
    Xenon::Engine
)

set_custom_output(Editor)
set_target_properties(Editor PROPERTIES FOLDER Examples)

add_custom_command(TARGET Editor PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets/
    $<TARGET_FILE_DIR:Editor>/assets/
)

if(NOT $<TARGET_FILE_DIR:Editor> STREQUAL ${PROJECT_BINARY_DIR})
    add_custom_command(TARGET Editor PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/assets/
        ${PROJECT_BINARY_DIR}/assets/
    )
endif()