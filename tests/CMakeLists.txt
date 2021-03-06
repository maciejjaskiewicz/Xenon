set(TEST_SRCROOT ${PROJECT_SOURCE_DIR}/tests/src)

set (TEST_MAIN ${TEST_SRCROOT}/TestMain.cpp)
set (TEST_UTILS
    ${TEST_SRCROOT}/Utils/ServiceLocator.cpp
    ${TEST_SRCROOT}/Utils/ImmutableServiceLocator.cpp
    ${TEST_SRCROOT}/Utils/TestService.hpp
    ${TEST_SRCROOT}/Utils/Delegate.cpp
)

set (TEST_SOURCES
    ${TEST_MAIN}
    ${TEST_UTILS}
)

source_group("" FILES ${TEST_MAIN})
source_group("Utils" FILES ${TEST_UTILS})

add_executable(XenonTest ${TEST_SOURCES})
target_link_libraries(XenonTest PRIVATE
    Xenon::Options
    Xenon::Warnings
    CONAN_PKG::gtest
    Xenon::Engine
)

gtest_discover_tests(XenonTest)