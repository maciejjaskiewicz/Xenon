project(CustomMain)

set (CUSTOM_MAIN_SOURCES
    src/CustomMain.cpp
)

add_executable(CustomMain ${CUSTOM_MAIN_SOURCES})
target_link_libraries(CustomMain PRIVATE
    Xenon::Options
    Xenon::Warnings
    Xenon::Engine
)

set_custom_output(CustomMain)
set_target_properties(CustomMain PROPERTIES FOLDER Examples)