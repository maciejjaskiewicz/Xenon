#include <Xenon/Xenon.hpp>

class Sandbox final : public Xenon::Application
{
public:
    Sandbox()
    {
        logger().info("Client test");
    }
};
XN_REGISTER_APPLICATION(Sandbox);

void Xenon::configureApplication(IApplicationBuilder<Sandbox>& applicationBuilder)
{
    applicationBuilder.configureApplicationLogger(
        [](ApplicationLoggerConfiguration& cfg)
    {
        cfg.setLabel("Sandbox");
        cfg.useConsoleLogger();
        cfg.useFileLogger("Sandbox.log", true);
    });
}