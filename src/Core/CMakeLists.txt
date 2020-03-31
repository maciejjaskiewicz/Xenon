set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Core)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Core)

# root sources
set (XN_SOURCES_CORE_ROOT_L
    ${XN_INCROOT}/Api.hpp
    ${XN_INCROOT}/Log.hpp
    ${XN_INCROOT}/Main.hpp
    ${XN_SRCROOT}/Application.cpp
    ${XN_INCROOT}/Application.hpp
    ${XN_INCROOT}/ApplicationServices.hpp
    ${XN_SRCROOT}/InternalApplicationServices.hpp
    ${XN_INCROOT}/ApplicationBuilder.hpp
    ${XN_SRCROOT}/Initializer.cpp
    ${XN_INCROOT}/Initializer.hpp
)

set (XN_SOURCES_CORE_ROOT
    ${XN_SOURCES_CORE_ROOT_L}
    PARENT_SCOPE
)

# window sources
set (XN_SOURCES_CORE_WINDOW_L
    ${XN_SRCROOT}/Window/Window.cpp
    ${XN_INCROOT}/Window/Window.hpp
    ${XN_INCROOT}/Window/WindowResolution.hpp
    ${XN_SRCROOT}/Window/WindowEventManager.cpp
    ${XN_INCROOT}/Window/WindowEventManager.hpp
)

set (XN_SOURCES_CORE_WINDOW
    ${XN_SOURCES_CORE_WINDOW_L}
    PARENT_SCOPE
)

# event sources
set (XN_SOURCES_CORE_EVENTS_L
    ${XN_INCROOT}/Events/WindowEvent.hpp
    ${XN_INCROOT}/Events/KeyEvent.hpp
    ${XN_INCROOT}/Events/MouseEvent.hpp
)

set (XN_SOURCES_CORE_EVENTS
    ${XN_SOURCES_CORE_EVENTS_L}
    PARENT_SCOPE
)

# input sources
set (XN_SOURCES_CORE_INPUT_L
    ${XN_SRCROOT}/Input/Input.cpp
    ${XN_INCROOT}/Input/Input.hpp
    ${XN_SRCROOT}/Input/NullInput.hpp
    ${XN_INCROOT}/Input/KeyCode.hpp
    ${XN_INCROOT}/Input/MouseCode.hpp
)

set (XN_SOURCES_CORE_INPUT
    ${XN_SOURCES_CORE_INPUT_L}
    PARENT_SCOPE
)

# gather sources
set (XN_SOURCES_CORE
    ${XN_SOURCES_CORE_ROOT_L}
    ${XN_SOURCES_CORE_WINDOW_L}
    ${XN_SOURCES_CORE_EVENTS_L}
    ${XN_SOURCES_CORE_INPUT_L}
    PARENT_SCOPE
)