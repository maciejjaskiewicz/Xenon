set(TEST_SRCROOT ${PROJECT_SOURCE_DIR}/tests/src)

set (TEST_SOURCES
    ${TEST_SRCROOT}/TestMain.cpp
    ${TEST_SRCROOT}/Dummy.cpp
)

add_executable(XenonTest ${TEST_SOURCES})
target_link_libraries(XenonTest CONAN_PKG::gtest)

target_include_directories(XenonTest PRIVATE ${PROJECT_SOURCE_DIR}/include)

gtest_discover_tests(XenonTest)

# disable PDBs warning for MSVC
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(Xenon PROPERTIES LINK_FLAGS "/ignore:4099")
endif()