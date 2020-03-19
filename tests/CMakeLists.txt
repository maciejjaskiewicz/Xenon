set(TEST_SRCROOT ${PROJECT_SOURCE_DIR}/tests/src)

set (TEST_SOURCES
    ${TEST_SRCROOT}/CatchMain.cpp
    ${TEST_SRCROOT}/Dummy.cpp
)

add_executable(XenonTest ${TEST_SOURCES})
target_link_libraries(XenonTest CONAN_PKG::catch2)

target_include_directories(XenonTest PRIVATE ${PROJECT_SOURCE_DIR}/include)

catch_discover_tests(XenonTest)