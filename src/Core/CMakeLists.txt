set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Core)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Core)

set (XN_SOURCES_CORE
    ${XN_INCROOT}/Api.hpp
    ${XN_INCROOT}/Log.hpp
    ${XN_INCROOT}/Main.hpp
    ${XN_SRCROOT}/Application.cpp
    ${XN_INCROOT}/Application.hpp
    ${XN_SRCROOT}/InternalApplicationServices.hpp
    ${XN_INCROOT}/ApplicationBuilder.hpp
    ${XN_SRCROOT}/Initializer.cpp
    ${XN_INCROOT}/Initializer.hpp
    ${XN_SRCROOT}/Window.cpp
    ${XN_INCROOT}/Window.hpp
    PARENT_SCOPE
)