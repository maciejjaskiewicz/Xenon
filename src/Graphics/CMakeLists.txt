set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Graphics)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Graphics)

set (XN_SOURCES_GRAPHICS
    ${XN_SRCROOT}/GraphicsContext.cpp
    ${XN_INCROOT}/GraphicsContext.hpp
    ${XN_SRCROOT}/BufferLayout.cpp
    ${XN_INCROOT}/BufferLayout.hpp
    ${XN_SRCROOT}/VertexBuffer.cpp
    ${XN_INCROOT}/VertexBuffer.hpp
    ${XN_SRCROOT}/IndexBuffer.cpp
    ${XN_INCROOT}/IndexBuffer.hpp
    ${XN_SRCROOT}/VertexArray.cpp
    ${XN_INCROOT}/VertexArray.hpp
    ${XN_SRCROOT}/Shader.cpp
    ${XN_INCROOT}/Shader.hpp
    ${XN_SRCROOT}/RendererAPI.cpp
    ${XN_INCROOT}/RendererAPI.hpp
    ${XN_SRCROOT}/RenderCmd.cpp
    ${XN_INCROOT}/RenderCmd.hpp
    ${XN_SRCROOT}/Renderer.cpp
    ${XN_INCROOT}/Renderer.hpp
    PARENT_SCOPE
)