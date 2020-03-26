#include <Xenon/Xenon.hpp>

class Sandbox final : public Xenon::Application
{
public:
    explicit Sandbox(const Xenon::ApplicationConfiguration& config)
        : Application(config)
    {
        XN_INFO("{} initialized", "Sandbox");
        Services::AppLogger::ref().warn("Static test");
    }
};
XN_REGISTER_APPLICATION(Sandbox);

void Xenon::configureApplication(IApplicationBuilder<Sandbox>& applicationBuilder)
{
    applicationBuilder.configureApplicationWindow(
        [](ApplicationWindowConfiguration& cfg)
    {
        cfg.setTitle("Sandbox application");
        cfg.maximize(false);
        cfg.setResolution(StandardWindowResolution::A_16X9_R_1280X720);
    });

    applicationBuilder.configureApplicationLogger(
        [](ApplicationLoggerConfiguration& cfg)
    {
        cfg.setLabel("Sandbox");
        cfg.useConsoleLogger();
        cfg.useFileLogger("Sandbox.log", true);
    });
}