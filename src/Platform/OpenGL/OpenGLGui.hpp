#pragma once

#include <Core/Gui/Gui.hpp>

namespace Xenon
{
    class OpenGLGui final : public Gui
    {
    public:
        explicit OpenGLGui(Window& window, const GuiConfiguration& guiConfiguration);
        ~OpenGLGui();

        void init() override;
        void newFrame() const override;
        void render() const override;
    private:
        Window& mWindow;
        GuiStyle mStyle;
        bool mDocking;
        bool mViewports;

        bool mInitialized{ false };
    };
}