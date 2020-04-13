#include <Xenon/Xenon.hpp>
#include <Xenon/Graphics.hpp>
#include <Xenon/Services/Time/Timer.hpp>

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

        mVertexArray = Xenon::VertexArray::create();

        float vertices[3 * 6] =
        {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        mVertexBuffer = Xenon::VertexBuffer::create(vertices, sizeof(vertices));

        const Xenon::BufferLayout layout =
        {
            { Xenon::DataType::Float3, "aPosition" },
            { Xenon::DataType::Float3, "aColor" }
        };
        mVertexBuffer->setLayout(layout);

        uint32_t indices[3] = { 0, 1, 2 };
        mIndexBuffer = Xenon::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));

        mVertexArray->pushVertexBuffer(mVertexBuffer);
        mVertexArray->bindIndexBuffer(mIndexBuffer);

        const std::string vertexShaderSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 aPosition;
            layout (location = 1) in vec3 aColor;

            out vec3 vColor;

            void main()
            {
                gl_Position = vec4(aPosition, 1.0);
                vColor = aColor;
            }
        )";

        const std::string fragmentShaderSrc = R"(
            #version 330 core

            out vec4 color;
            in vec3 vColor;

            void main()
            {
                color = vec4(vColor, 1.0);
            }
        )";

        mShader = Xenon::Shader::create(vertexShaderSrc, fragmentShaderSrc);
    }

    void update(const Xenon::DeltaTime& deltaTime) override
    {
        auto& renderer = Services::Renderer::ref();

        Xenon::RenderCmd::setClearColor(mClearColor);
        Xenon::RenderCmd::clear();

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

        renderer.beginScene();

        mShader->bind();
        renderer.submit(mVertexArray);

        renderer.endScene();
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

    glm::vec4 mClearColor{ 0.2f, 0.3f, 0.3f, 1.0f };

    std::shared_ptr<Xenon::VertexBuffer> mVertexBuffer;
    std::shared_ptr<Xenon::IndexBuffer> mIndexBuffer;
    std::shared_ptr<Xenon::VertexArray> mVertexArray;
    std::shared_ptr<Xenon::Shader> mShader;
};
XN_REGISTER_APPLICATION(Sandbox)

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