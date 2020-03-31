#define XN_CUSTOM_MAIN
#include <Xenon/Xenon.hpp>

class Custom final : public Xenon::Application
{
public:
    explicit Custom(const Xenon::ApplicationConfiguration& config)
        : Application(config)
    {
        Services::Logger::ref().info("Client test");
    }

    void update() override
    {
        
    }
};

int main()
{
    auto appBuild = Xenon::ApplicationBuilder<Custom>();
    appBuild.configureApplicationLogger([](auto& cfg){
        cfg.useConsoleLogger();
        cfg.useFileLogger("Custom.log", true);
    });

    const auto application = appBuild.build();
    application->run();

    return 0;
}