#include <Xenon/Xenon.hpp>
#include <Xenon/Graphics.hpp>
#include <Xenon/Services/Time/Timer.hpp>
#include <Xenon/Utils/ResourceCache.hpp>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <numeric>

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

        float vertices[4 * 5] =
        {
            -0.8f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.8f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.8f,  0.5f, 0.0f, 0.0f, 1.0f,
             0.8f,  0.5f, 0.0f, 1.0f, 1.0f
        };
        mVertexBuffer = Xenon::VertexBuffer::create(vertices, sizeof(vertices));

        const Xenon::BufferLayout layout =
        {
            { Xenon::DataType::Float3, "aPosition" },
            { Xenon::DataType::Float2, "aTextureCoordinate" }
        };
        mVertexBuffer->setLayout(layout);

        uint32_t indices[2 * 3] = 
        {
            0, 1, 2,
            2, 1, 3
        };
        mIndexBuffer = Xenon::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));

        mVertexArray->pushVertexBuffer(mVertexBuffer);
        mVertexArray->bindIndexBuffer(mIndexBuffer);

        mTextureCache.set<Xenon::Texture2DLoader>("world", Xenon::Texture2DLoaderArgs(
            "assets/textures/world.png"));
        mShaderCache.set<Xenon::ShaderLoader>("texture", Xenon::ShaderLoaderArgs(
            "assets/shaders/TextureVertex.glsl", 
            "assets/shaders/TextureFragment.glsl"));

        mCameraController = std::make_unique<Xenon::OrthographicCameraController>(
            config.windowConfiguration.resolution().aspectRatio(), true
        );
    }

    void update(const Xenon::DeltaTime& deltaTime) override
    {
        auto& renderer = Services::Renderer::ref();
        const auto shader = mShaderCache.load("texture");

        Xenon::RenderCmd::setClearColor(mClearColor);
        Xenon::RenderCmd::clear();

        mCameraController->update(deltaTime);

        renderer.beginScene(mCameraController->camera());

        mTextureCache.load("world")->bind();
        shader->bind();
        shader->setInt("uTexture", 0);
        renderer.submit(shader, mVertexArray);

        renderer.endScene();
    }

    void updateGui(const Xenon::DeltaTime& deltaTime) override
    {
        ImGui::Begin("Application Debug");

        const auto rendererDetails = Services::Renderer::ref().getDetails();

        const auto buffSize = 60;
        static float frameRateBuff[buffSize];
        static auto frameRateBuffIdx = 0;

        frameRateBuff[frameRateBuffIdx] = deltaTime.milliseconds();
        frameRateBuffIdx = (frameRateBuffIdx + 1) % buffSize;

        const auto sum = std::accumulate(frameRateBuff, frameRateBuff + buffSize, 0.0f);
        const auto avg = sum / buffSize;

        ImGui::Text("API: %s %s", rendererDetails.name.c_str(), rendererDetails.version.c_str());
        ImGui::Text("Vendor: %s", rendererDetails.vendor.c_str());
        ImGui::Text("Renderer: %s", rendererDetails.renderer.c_str());
        ImGui::Text("Up time: %.2f s", Services::Timer::ref().elapsed());
        ImGui::Text("Frame rate: %.3f ms/frame (%.1f FPS)", avg, 1000.0f / avg);
        
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
    Xenon::ResourceCache<Xenon::Shader> mShaderCache;
    Xenon::ResourceCache<Xenon::Texture2D> mTextureCache;

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
        cfg.setVSync(false);
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