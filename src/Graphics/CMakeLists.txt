set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Graphics)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Graphics)

# root sources
set (XN_SOURCES_GRAPHICS_ROOT_L
    ${XN_SRCROOT}/RenderCmd.cpp
    ${XN_INCROOT}/RenderCmd.hpp
    ${XN_SRCROOT}/Renderer.cpp
    ${XN_INCROOT}/Renderer.hpp
)

set (XN_SOURCES_GRAPHICS_ROOT
    ${XN_SOURCES_GRAPHICS_ROOT_L}
    PARENT_SCOPE
)

# API sources
set (XN_SOURCES_GRAPHICS_API_L
    ${XN_SRCROOT}/API/GraphicsContext.cpp
    ${XN_INCROOT}/API/GraphicsContext.hpp
    ${XN_SRCROOT}/API/BufferLayout.cpp
    ${XN_INCROOT}/API/BufferLayout.hpp
    ${XN_SRCROOT}/API/VertexBuffer.cpp
    ${XN_INCROOT}/API/VertexBuffer.hpp
    ${XN_SRCROOT}/API/IndexBuffer.cpp
    ${XN_INCROOT}/API/IndexBuffer.hpp
    ${XN_SRCROOT}/API/VertexArray.cpp
    ${XN_INCROOT}/API/VertexArray.hpp
    ${XN_SRCROOT}/API/Shader.cpp
    ${XN_INCROOT}/API/Shader.hpp
    ${XN_INCROOT}/API/Texture.hpp
    ${XN_SRCROOT}/API/Texture2D.cpp
    ${XN_INCROOT}/API/Texture2D.hpp
    ${XN_SRCROOT}/API/RendererAPI.cpp
    ${XN_INCROOT}/API/RendererAPI.hpp
    ${XN_INCROOT}/API/RendererAPIDetails.hpp
)

set (XN_SOURCES_GRAPHICS_API
    ${XN_SOURCES_GRAPHICS_API_L}
    PARENT_SCOPE
)

# camera sources
set (XN_SOURCES_GRAPHICS_CAMERA_L
    ${XN_SRCROOT}/Camera/Camera.cpp
    ${XN_INCROOT}/Camera/Camera.hpp
    ${XN_SRCROOT}/Camera/CameraController.cpp
    ${XN_INCROOT}/Camera/CameraController.hpp
    ${XN_SRCROOT}/Camera/OrthographicCamera.cpp
    ${XN_INCROOT}/Camera/OrthographicCamera.hpp
    ${XN_SRCROOT}/Camera/OrthographicCameraController.cpp
    ${XN_INCROOT}/Camera/OrthographicCameraController.hpp
)

set (XN_SOURCES_GRAPHICS_CAMERA
    ${XN_SOURCES_GRAPHICS_CAMERA_L}
    PARENT_SCOPE
)

# gather sources
set (XN_SOURCES_GRAPHICS
    ${XN_SOURCES_GRAPHICS_ROOT_L}
    ${XN_SOURCES_GRAPHICS_API_L}
    ${XN_SOURCES_GRAPHICS_CAMERA_L}
    PARENT_SCOPE
)