#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_glfw.cpp>

#include "OpenGLGui.hpp"

namespace Xenon
{
    OpenGLGui::OpenGLGui(Window& window, const GuiConfiguration& guiConfiguration)
        : mWindow(window), mStyle(guiConfiguration.style), mDocking(guiConfiguration.docking),
          mViewports(guiConfiguration.viewports)
    { }

    void OpenGLGui::init()
    {
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();
        auto& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        if (mDocking) io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        if (mViewports) io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        switch (mStyle)
        {
        case GuiStyle::Classic: ImGui::StyleColorsClassic(); break;
        case GuiStyle::Light: ImGui::StyleColorsLight(); break;
        case GuiStyle::Dark: ImGui::StyleColorsDark(); break;
        default: ImGui::StyleColorsDark();
        }

        auto& style = ImGui::GetStyle();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        auto* glfwWindow = static_cast<GLFWwindow*>(mWindow.window());

        ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
        ImGui_ImplOpenGL3_Init("#version 410");

        mInitialized = true;
        XN_ENG_DEBUG("ImGui successfully initialized");
    }

    OpenGLGui::~OpenGLGui()
    {
        if(mInitialized)
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    }

    void OpenGLGui::newFrame() const
    {
        XN_ASSERT_COM(mInitialized, "GUI is uninitialized!");

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void OpenGLGui::render() const
    {
        XN_ASSERT_COM(mInitialized, "GUI is uninitialized!");

        auto& io = ImGui::GetIO();

        const auto resolution = mWindow.resolution();
        io.DisplaySize = ImVec2(
            static_cast<float>(resolution.width), 
            static_cast<float>(resolution.height)
        );

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            auto* backupCurrentContext = glfwGetCurrentContext();

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();

            glfwMakeContextCurrent(backupCurrentContext);
        }
    }
}