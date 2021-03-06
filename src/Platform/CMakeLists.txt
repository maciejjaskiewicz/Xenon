set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Platform)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Platform)

set (XN_SOURCES_PLATFORM_GLFW_L
    ${XN_SRCROOT}/GLFW/GLFWWindow.cpp
    ${XN_SRCROOT}/GLFW/GLFWWindow.hpp
    ${XN_SRCROOT}/GLFW/GLFWWindowEventManager.cpp
    ${XN_SRCROOT}/GLFW/GLFWWindowEventManager.hpp
    ${XN_SRCROOT}/GLFW/GLFWInput.cpp
    ${XN_SRCROOT}/GLFW/GLFWInput.hpp
)

set (XN_SOURCES_PLATFORM_GLFW
    ${XN_SOURCES_PLATFORM_GLFW_L}
    PARENT_SCOPE
)

set (XN_SOURCES_PLATFORM_OPENGL_L
    ${XN_SRCROOT}/OpenGL/OpenGLGui.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLGui.hpp
    ${XN_SRCROOT}/OpenGL/OpenGLContext.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLContext.hpp
    ${XN_SRCROOT}/OpenGL/OpenGLVertexBuffer.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLVertexBuffer.hpp
    ${XN_SRCROOT}/OpenGL/OpenGLIndexBuffer.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLIndexBuffer.hpp
    ${XN_SRCROOT}/OpenGL/OpenGLVertexArray.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLVertexArray.hpp
    ${XN_SRCROOT}/OpenGL/OpenGLFrameBuffer.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLFrameBuffer.hpp
    ${XN_SRCROOT}/OpenGL/OpenGLShader.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLShader.hpp
    ${XN_SRCROOT}/OpenGL/OpenGLTexture2D.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLTexture2D.hpp
    ${XN_SRCROOT}/OpenGL/OpenGLRendererAPI.cpp
    ${XN_SRCROOT}/OpenGL/OpenGLRendererAPI.hpp
)

set (XN_SOURCES_PLATFORM_OPENGL
    ${XN_SOURCES_PLATFORM_OPENGL_L}
    PARENT_SCOPE
)

set (XN_SOURCES_PLATFORM
    ${XN_SOURCES_PLATFORM_GLFW_L}
    ${XN_SOURCES_PLATFORM_OPENGL_L}
    PARENT_SCOPE
)