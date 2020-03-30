set(XN_INCROOT ${PROJECT_SOURCE_DIR}/include/Xenon/Services)
set(XN_SRCROOT ${PROJECT_SOURCE_DIR}/src/Services)

set (XN_SOURCES_SERVICES_LOG_L
    ${XN_SRCROOT}/Log/Logger.cpp
    ${XN_INCROOT}/Log/Logger.hpp
    ${XN_SRCROOT}/Log/InternalLogger.hpp
    ${XN_SRCROOT}/Log/LogSink.hpp
    ${XN_SRCROOT}/Log/ConsoleLogSink.cpp
    ${XN_SRCROOT}/Log/ConsoleLogSink.hpp
    ${XN_SRCROOT}/Log/FileLogSink.cpp
    ${XN_SRCROOT}/Log/FileLogSink.hpp
)

set (XN_SOURCES_SERVICES_LOG
    ${XN_SOURCES_SERVICES_LOG_L}
    PARENT_SCOPE
)

set (XN_SOURCES_SERVICES_EVENT_L
    ${XN_INCROOT}/Event/Event.hpp
    ${XN_INCROOT}/Event/EventSubject.hpp
    ${XN_INCROOT}/Event/EventBus.hpp
)

set (XN_SOURCES_SERVICES_EVENT
    ${XN_SOURCES_SERVICES_EVENT_L}
    PARENT_SCOPE
)

set (XN_SOURCES_SERVICES
    ${XN_SOURCES_SERVICES_LOG_L}
    ${XN_SOURCES_SERVICES_EVENT_L}
    PARENT_SCOPE
)