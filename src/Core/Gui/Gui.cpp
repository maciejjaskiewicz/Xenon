#include <Xenon/Core/Gui/Gui.hpp>

#include "../../Platform/OpenGL/OpenGLGui.hpp"

namespace Xenon
{
    std::unique_ptr<Gui> Gui::create(Window& window)
    {
        return std::make_unique<OpenGLGui>(window);
    }
}