set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Config)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Config)

set (XN_SOURCES_CONFIG
    ${XN_INCROOT}/ApplicationConfiguration.hpp
    ${XN_SRCROOT}/ApplicationLoggerConfiguration.cpp
    ${XN_INCROOT}/ApplicationLoggerConfiguration.hpp
    ${XN_SRCROOT}/ApplicationWindowConfiguration.cpp
    ${XN_INCROOT}/ApplicationWindowConfiguration.hpp
    PARENT_SCOPE
)