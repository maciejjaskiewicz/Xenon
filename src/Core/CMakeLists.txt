set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src)

set (XN_SOURCES_CORE
    ${XN_INCROOT}/Core/Api.hpp
    ${XN_INCROOT}/Core/Assert.hpp
    ${XN_SRCROOT}/Core/Application.cpp
    ${XN_INCROOT}/Core/Application.hpp
    ${XN_INCROOT}/Core/Platform.hpp
    PARENT_SCOPE
)