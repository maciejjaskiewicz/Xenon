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
            -0.75f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.75f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
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

            uniform mat4 uViewProjection;

            out vec3 vColor;

            void main()
            {
                gl_Position = uViewProjection * vec4(aPosition, 1.0);
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

        mCameraController = std::make_unique<Xenon::OrthographicCameraController>(
            config.windowConfiguration.resolution().aspectRatio(), true
        );
    }

    void update(const Xenon::DeltaTime& deltaTime) override
    {
        auto& renderer = Services::Renderer::ref();

        Xenon::RenderCmd::setClearColor(mClearColor);
        Xenon::RenderCmd::clear();

        mCameraController->update(deltaTime);

        renderer.beginScene(mCameraController->camera());
        renderer.submit(mShader, mVertexArray);
        renderer.endScene();
    }

    void updateGui(const Xenon::DeltaTime& deltaTime) override
    {
        ImGui::Begin("Application Debug");

        const auto rendererDetails = Services::Renderer::ref().getDetails();

        ImGui::Text("API: %s %s", rendererDetails.name.c_str(), rendererDetails.version.c_str());
        ImGui::Text("Vendor: %s", rendererDetails.vendor.c_str());
        ImGui::Text("Renderer: %s", rendererDetails.renderer.c_str());
        ImGui::Text("Up time: %.2f s", Services::Timer::ref().elapsed());
        ImGui::Text("Frame rate: %.3f ms/frame (%.1f FPS)", deltaTime.milliseconds(), 1000.0f / deltaTime.milliseconds());
        
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

        mCameraController->updateDebugGui(deltaTime);
    }

private:
    inline static bool mShowImGuiDemo{ false };

    glm::vec4 mClearColor{ 0.15f, 0.15f, 0.15f, 1.0f };

    std::shared_ptr<Xenon::VertexBuffer> mVertexBuffer;
    std::shared_ptr<Xenon::IndexBuffer> mIndexBuffer;
    std::shared_ptr<Xenon::VertexArray> mVertexArray;
    std::shared_ptr<Xenon::Shader> mShader;

    std::unique_ptr<Xenon::OrthographicCameraController> mCameraController;
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