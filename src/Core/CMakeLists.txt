set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Core)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Core)

set (XN_SOURCES_CORE
    ${XN_INCROOT}/Api.hpp
    ${XN_INCROOT}/Assert.hpp
    ${XN_SRCROOT}/Application.cpp
    ${XN_INCROOT}/Application.hpp
    ${XN_INCROOT}/Platform.hpp
    PARENT_SCOPE
)