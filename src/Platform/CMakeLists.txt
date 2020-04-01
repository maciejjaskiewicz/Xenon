set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Platform)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Platform)

set (XN_SOURCES_PLATFORM_COMMON_L
    ${XN_SRCROOT}/Common/CommonWindow.cpp
    ${XN_SRCROOT}/Common/CommonWindow.hpp
    ${XN_SRCROOT}/Common/CommonWindowEventManager.cpp
    ${XN_SRCROOT}/Common/CommonWindowEventManager.hpp
    ${XN_SRCROOT}/Common/CommonInput.cpp
    ${XN_SRCROOT}/Common/CommonInput.hpp
)

set (XN_SOURCES_PLATFORM_COMMON
    ${XN_SOURCES_PLATFORM_COMMON_L}
    PARENT_SCOPE
)

set (XN_SOURCES_PLATFORM_OPENGL_L
    ${XN_SRCROOT}/OpenGL/OpenGLGui.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLGui.hpp
)

set (XN_SOURCES_PLATFORM_OPENGL
    ${XN_SOURCES_PLATFORM_OPENGL_L}
    PARENT_SCOPE
)

set (XN_SOURCES_PLATFORM
    ${XN_SOURCES_PLATFORM_COMMON_L}
    ${XN_SOURCES_PLATFORM_OPENGL_L}
    PARENT_SCOPE
)