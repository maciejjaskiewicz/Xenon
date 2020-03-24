#define XN_CUSTOM_MAIN
#include <Xenon/Xenon.hpp>

class Custom final : public Xenon::Application
{
public:
    Custom()
    {
        Services::AppLogger::ref().info("Client test");
    }
};

int main()
{
    auto appBuild = Xenon::ApplicationBuilder<Custom>();
    appBuild.configureApplicationLogger([](auto& cfg){
        cfg.useConsoleLogger();
        cfg.useFileLogger("Custom.log", true);
    });

    auto application = appBuild.build();
    application->run();

    return 0;
}