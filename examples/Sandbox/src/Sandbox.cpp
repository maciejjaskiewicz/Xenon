#include <Xenon/Xenon.hpp>
#include <Xenon/Core/Events/KeyEvent.hpp>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

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

    void updateGui() override
    {
        ImGui::Begin("Debug");

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
        ImGui::Text("%d active windows (%d visible)", io.MetricsActiveWindows, io.MetricsRenderWindows);
        ImGui::Separator();

        ImGui::ColorEdit4("Clear Color", glm::value_ptr(mClearColor));
        if(!mShowImGuiDemo)
        {
            mShowImGuiDemo = ImGui::Button("Run ImGui demo", ImVec2(200, 30));
        }

        ImGui::End();

        if(mShowImGuiDemo)
        {
            ImGui::ShowDemoWindow(&mShowImGuiDemo);
        }
    }

private:
    inline static bool mShowImGuiDemo{ false };
};
XN_REGISTER_APPLICATION(Sandbox);

void Xenon::configureApplication(IApplicationBuilder<Sandbox>& applicationBuilder)
{
    applicationBuilder.configureApplicationWindow([](ApplicationWindowConfiguration& cfg)
    {
        cfg.setTitle("Sandbox application");
        cfg.maximize(false);
        cfg.setResolution(StandardWindowResolution::A_16X9_R_1280X720);
        cfg.setVSync(true);
    });

    applicationBuilder.configureApplicationLogger([](ApplicationLoggerConfiguration& cfg)
    {
        cfg.setLabel("Sandbox");
        cfg.useConsoleLogger();
        cfg.useFileLogger("Sandbox.log", true);
    });

    applicationBuilder.configureApplicationGui([](ApplicationGuiConfiguration& cfg)
    {
        cfg.setStyle(GuiStyle::Dark);
        cfg.useDocking();
    });
}