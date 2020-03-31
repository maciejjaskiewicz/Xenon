#include <Xenon/Core/Window/Window.hpp>

#include "../../Platform/Common/CommonWindow.hpp"

namespace Xenon
{
    XN_NODISCARD std::unique_ptr<Window> Window::create(const std::string& title,
        const WindowResolution& resolution, bool vSync, bool maximized)
    {
        return std::make_unique<CommonWindow>(title, resolution, vSync, maximized);
    }

    XN_NODISCARD std::unique_ptr<Window> Window::create(const ApplicationWindowConfiguration& windowConfiguration)
    {
        return std::make_unique<CommonWindow>(windowConfiguration);
    }
}