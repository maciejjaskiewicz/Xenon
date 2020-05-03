#include <Xenon/Xenon.hpp>
#include <Xenon/Graphics.hpp>

#include <imgui.h>
#include <imgui_internal.h>

#include <ImGuiFileDialog.hpp>

class EditorApp final : public Xenon::Application
{
public:
    explicit EditorApp(const Xenon::ApplicationConfiguration& config)
        : Application(config)
    {
        Services::EventBus::ref().subscribe<Xenon::KeyReleasedEvent>(
            [this](const Xenon::KeyReleasedEvent& event)
        {
            if (event.keyCode == XN_KEY_ESCAPE)
            {
                XN_INFO("Closing from EditorApp");
                mRunning = false;
            }
        });

        setStyle();
    }

    void init() override
    {
        mFrameBuffer = Xenon::FrameBuffer::create(640, 480);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        uint32_t indices[3] = { 0, 1, 2 };

        mVertexBuffer = Xenon::VertexBuffer::create(vertices, sizeof(vertices));
        mIndexBuffer = Xenon::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));

        const Xenon::BufferLayout bufferLayout = {
            { Xenon::DataType::Float3, "aPosition" }
        };
        mVertexBuffer->setLayout(bufferLayout);

        mVertexArray = Xenon::VertexArray::create();
        mVertexArray->pushVertexBuffer(mVertexBuffer);
        mVertexArray->bindIndexBuffer(mIndexBuffer);

        mShader = mShaderCache.load<Xenon::ShaderLoader>("flat", Xenon::ShaderLoaderArgs(
            "assets/shaders/FlatColorVertex.glsl",
            "assets/shaders/FlatColorFragment.glsl"
        ));

        mCamera = std::make_shared<Xenon::OrthographicCamera>(Xenon::OrthographicCameraProjConfiguration{
            -1.0f, 1.0f, -1.0f, 1.0f
        });
    }

    void update(const Xenon::DeltaTime& deltaTime) override
    {
        Xenon::RenderCmd::setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        Xenon::RenderCmd::clear();

        auto& renderer = Services::Renderer::ref();

        mFrameBuffer->bind();
        renderer.beginScene(*mCamera);

        Xenon::RenderCmd::setClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
        Xenon::RenderCmd::clear();

        mShader->bind();
        mShader->setFloat4("uColor", glm::vec4(0.3f, 0.8f, 0.2f, 1.0f));
        renderer.submit(mShader, mVertexArray);

        renderer.endScene();
        mFrameBuffer->unbind();
    }

    void updateGui(const Xenon::DeltaTime& deltaTime) override
    {
        beginDockSpace();

        drawMenuBar();

        static auto open = true;
        const auto sceneFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);

        ImGui::Begin("Scene", &open, sceneFlags);

        const auto pos = ImGui::GetCursorScreenPos();
        const auto imGuiWindowSize = ImGui::GetWindowSize();
        const auto windowSize = Xenon::WindowResolution(
            static_cast<uint32_t>(imGuiWindowSize.x),
            static_cast<uint32_t>(imGuiWindowSize.y)
        );

        if(windowSize != mWindowSize)
        {
            mFrameBuffer = Xenon::FrameBuffer::create(windowSize.width, windowSize.height);
            mWindowSize = windowSize;

            mCamera->setProjection(Xenon::OrthographicCameraProjConfiguration{ 
                -windowSize.aspectRatio(),
                windowSize.aspectRatio(),
                -1.0f,
                1.0f
            });
        }

        auto* texturePtr =  reinterpret_cast<void*>(static_cast<intptr_t>(mFrameBuffer->texture().id()));
        const auto textureWidth = static_cast<float>(mFrameBuffer->texture().width());
        const auto textureHeight = static_cast<float>(mFrameBuffer->texture().height());

        ImGui::GetWindowDrawList()->AddImage(texturePtr, pos, ImVec2(pos.x + textureWidth, pos.y + textureHeight),
            ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();

        ImGui::ShowMetricsWindow();
        ImGui::ShowDemoWindow();

        endDockSpace();

        if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
        {
            if (igfd::ImGuiFileDialog::Instance()->IsOk == true)
            {
                std::string filePathName = igfd::ImGuiFileDialog::Instance()->GetFilepathName();
                std::string filePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();
            }

            igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
        }
    }


private:
    std::shared_ptr<Xenon::FrameBuffer> mFrameBuffer;
    std::shared_ptr<Xenon::VertexBuffer> mVertexBuffer;
    std::shared_ptr<Xenon::IndexBuffer> mIndexBuffer;
    std::shared_ptr<Xenon::VertexArray> mVertexArray;
    std::shared_ptr<Xenon::OrthographicCamera> mCamera;
    std::shared_ptr<Xenon::Shader> mShader;

    Xenon::ResourceCache<Xenon::Shader> mShaderCache;

    Xenon::WindowResolution mWindowSize{ 0, 0 };


    void beginDockSpace() const
    {
        static auto p_open = true;
        static ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking;
        ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
            windowFlags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, windowFlags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        const ImGuiID dockSpaceId = ImGui::GetID("TestDockSpace");

        static auto firstTime = true;
        if (firstTime)
        {
            ImGui::DockBuilderRemoveNode(dockSpaceId);
            ImGui::DockBuilderAddNode(dockSpaceId, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockSpaceId, viewport->Size);

            ImGuiID dockRightId, dockUpId;
            const ImGuiID dockMainId = dockSpaceId;
            const ImGuiID sceneId = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Left, 0.7f, nullptr, &dockRightId);
            const ImGuiID demoId = ImGui::DockBuilderSplitNode(dockRightId, ImGuiDir_Down, 0.7f, nullptr, &dockUpId);

            ImGui::DockBuilderDockWindow("Scene", sceneId);
            ImGui::DockBuilderDockWindow("Dear ImGui Demo", demoId);
            ImGui::DockBuilderDockWindow("Dear ImGui Metrics", dockUpId);
            ImGui::DockBuilderFinish(dockSpaceId);

            firstTime = false;
        }

        ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), dockSpaceFlags);
    }

    static void endDockSpace()
    {
        ImGui::End();
    }

    void drawMenuBar() const
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.0f, 5.0f));

        if(ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::MenuItem("Exit");
                if(ImGui::MenuItem("Open File"))
                {
                    igfd::ImGuiFileDialog::Instance()->OpenModal("ChooseFileDlgKey", "Choose File", ".cpp\0.h\0.hpp\0\0", ".");
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                ImGui::MenuItem("Test");
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Windows"))
            {
                ImGui::MenuItem("Test");
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::PopStyleVar();
    }

    void setStyle() const
    {
        auto& io = ImGui::GetIO();

        auto font = io.Fonts->AddFontFromFileTTF("assets/fonts/Ruda-Bold.ttf", 15.0f);
        mGui->setFont(font);

        ImGui::GetStyle().FrameRounding = 4.0f;
        ImGui::GetStyle().GrabRounding = 4.0f;

        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }

};
XN_REGISTER_APPLICATION(EditorApp)

void Xenon::configureApplication(IApplicationBuilder<EditorApp>& applicationBuilder)
{
    applicationBuilder.configureApplicationWindow([](ApplicationWindowConfiguration& cfg)
    {
        cfg.setTitle("Editor sandbox");
        cfg.maximize(false);
        cfg.setResolution(StandardWindowResolution::A_16X9_R_1280X720);
        cfg.setVSync(true);
    });

    applicationBuilder.configureApplicationLogger([](ApplicationLoggerConfiguration& cfg)
    {
        cfg.setLabel("EditorApp");
        cfg.useConsoleLogger();
        cfg.useFileLogger("EditorApp.log", true);
    });

    applicationBuilder.configureApplicationGui([](ApplicationGuiConfiguration& cfg)
    {
        cfg.setStyle(GuiStyle::Dark);
        cfg.useDocking();
    });
}