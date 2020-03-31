#pragma once

#include "../Api.hpp"
#include "../../Config/ApplicationWindowConfiguration.hpp"

#include <string>
#include <memory>

namespace Xenon
{
    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void update() const = 0;
        virtual void setVSync(bool enabled) = 0;

        XN_NODISCARD virtual void* window() const noexcept = 0;
        XN_NODISCARD virtual WindowResolution resolution() const noexcept = 0;
        XN_NODISCARD virtual bool vSync() const noexcept = 0;
        XN_NODISCARD virtual bool maximized() const noexcept = 0;

        XN_NODISCARD static std::unique_ptr<Window> create(
            const std::string& title = "Xenon",
            const WindowResolution& resolution = WindowResolution(),
            bool vSync = false,
            bool maximized = false);

        XN_NODISCARD static std::unique_ptr<Window> create(
            const ApplicationWindowConfiguration& windowConfiguration);
    };
}
