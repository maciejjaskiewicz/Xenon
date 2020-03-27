set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Utils)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Utils)

set (XN_SOURCES_UTILS
    ${XN_INCROOT}/ServiceLocator.hpp
    ${XN_INCROOT}/ImmutableServiceLocator.hpp
    ${XN_INCROOT}/Delegate.hpp
    PARENT_SCOPE
)