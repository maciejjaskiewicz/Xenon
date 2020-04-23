set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Utils)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Utils)

set (XN_SOURCES_UTILS
    ${XN_INCROOT}/ServiceLocator.hpp
    ${XN_INCROOT}/ImmutableServiceLocator.hpp
    ${XN_INCROOT}/Delegate.hpp
    ${XN_SRCROOT}/DeltaTime.cpp
    ${XN_INCROOT}/DeltaTime.hpp
    ${XN_INCROOT}/ResourceLoader.hpp
    ${XN_INCROOT}/ResourceCache.hpp
    PARENT_SCOPE
)