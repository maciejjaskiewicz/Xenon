#pragma once

#include "ApplicationBuilder.hpp"

#include <memory>

#ifndef XN_CUSTOM_MAIN

#define XN_REGISTER_APPLICATION(applicationType)                                            \
    typedef Xenon::IApplicationBuilder<applicationType> AppBuilder;                         \
                                                                                            \
    namespace Xenon                                                                         \
    {                                                                                       \
        extern void configureApplication(AppBuilder& applicationBuilder);                   \
    }                                                                                       \
                                                                                            \
    int main(int argc, char** argv)                                                         \
    {                                                                                       \
        auto appBuild = Xenon::ApplicationBuilder<applicationType>();                       \
        Xenon::configureApplication(appBuild);                                              \
        auto application = appBuild.build();                                                \
                                                                                            \
        application->run();                                                                 \
                                                                                            \
        return 0;                                                                           \
    }                                                                                       \

#endif
