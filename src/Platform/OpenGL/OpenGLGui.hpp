#pragma once

#include <Xenon/Core/Gui/Gui.hpp>

namespace Xenon
{
    class OpenGLGui final : public Gui
    {
    public:
        explicit OpenGLGui(Window& window);
        ~OpenGLGui();

        void newFrame() const override;
        void render() const override;
    private:
        Window& mWindow;
    };
}