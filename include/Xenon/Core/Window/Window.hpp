#pragma once

#include "../Api.hpp"
#include "../../Config/ApplicationWindowConfiguration.hpp"

#include <string>
#include <memory>

namespace Xenon
{
    struct WindowConfiguration
    {
        std::string title{ "Xenon application" };
        WindowResolution resolution{ StandardWindowResolution::A_16X9_R_1280X720 };
        bool vSync{ false };
        bool maximized{ false };

        explicit WindowConfiguration(const ApplicationWindowConfiguration& appWindowCfg)
            : title(appWindowCfg.title()), resolution(appWindowCfg.resolution()),
              vSync(appWindowCfg.vSync()), maximized(appWindowCfg.maximized())
        { }
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void init() = 0;
        virtual void update() const = 0;
        virtual void setVSync(bool enabled) = 0;

        XN_NODISCARD virtual void* window() const noexcept = 0;
        XN_NODISCARD virtual WindowResolution resolution() const noexcept = 0;
        XN_NODISCARD virtual bool vSync() const noexcept = 0;
        XN_NODISCARD virtual bool maximized() const noexcept = 0;
        XN_NODISCARD virtual bool minimized() const noexcept = 0;

        XN_NODISCARD static std::unique_ptr<Window> create(const WindowConfiguration& windowConfiguration);
    };
}
