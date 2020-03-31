#include <Xenon/Core/Window/WindowEventManager.hpp>

#include "../../Platform/Common/CommonWindowEventManager.hpp"

namespace Xenon
{
    XN_NODISCARD std::unique_ptr<WindowEventManager> WindowEventManager::create(Window& window)
    {
        return std::make_unique<CommonWindowEventManager>(window);
    }
}