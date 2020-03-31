#include <Xenon/Xenon.hpp>
#include <Xenon/Core/Events/KeyEvent.hpp>

class Sandbox final : public Xenon::Application
{
public:
    explicit Sandbox(const Xenon::ApplicationConfiguration& config)
        : Application(config)
    {
        XN_INFO("{} initialized", "Sandbox");

        Services::EventBus::ref().subscribe<Xenon::KeyReleasedEvent>(
            [this](const Xenon::KeyReleasedEvent& event)
        {
            if(event.keyCode == XN_KEY_ESCAPE)
            {
                XN_INFO("Closing from Sandbox");
                mRunning = false;
            }
        });
    }

    void update() override
    {
        if(Services::Input::ref().isKeyPressed(Xenon::KeyCode::Space))
        {
            XN_DEBUG("Space is pressed");
        }

        if (Services::Input::ref().isMouseButtonPressed(Xenon::MouseButtonCode::ButtonRight))
        {
            auto [x, y] = Services::Input::ref().mousePosition();

            XN_DEBUG("Right mouse button is pressed");
            XN_DEBUG("Mouse possition: X={}, Y={}", x, y);
        }
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
        cfg.setVSync(true);
    });

    applicationBuilder.configureApplicationLogger(
        [](ApplicationLoggerConfiguration& cfg)
    {
        cfg.setLabel("Sandbox");
        cfg.useConsoleLogger();
        cfg.useFileLogger("Sandbox.log", true);
    });
}