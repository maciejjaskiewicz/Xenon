#define XN_CUSTOM_MAIN
#include <Xenon/Xenon.hpp>
#include <Xenon/Graphics.hpp>

class Custom final : public Xenon::Application
{
public:
    explicit Custom(const Xenon::ApplicationConfiguration& config)
        : Application(config)
    {
        Services::Logger::ref().info("Client test");
    }

    void update(const Xenon::DeltaTime& deltaTime) override
    {
        Xenon::RenderCmd::setClearColor(glm::vec4{ 0.2f, 0.3f, 0.3f, 1.0f });
        Xenon::RenderCmd::clear();
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