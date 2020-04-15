#pragma once

#include "Xenon/Core/Api.hpp"
#include "Xenon/Core/Window/WindowResolution.hpp"

#include <string>

namespace Xenon
{
    class ApplicationWindowConfiguration
    {
    public:
        explicit ApplicationWindowConfiguration();

        void setTitle(const std::string& title);
        void setResolution(const WindowResolution& resolution) noexcept;
        void maximize(bool maximize = true) noexcept;
        void setVSync(bool enabled) noexcept;

        XN_NODISCARD std::string title() const;
        XN_NODISCARD WindowResolution resolution() const;
        XN_NODISCARD bool maximized() const;
        XN_NODISCARD bool vSync() const;
    private:
        std::string mTitle{ "Xenon application" };
        WindowResolution mResolution{ StandardWindowResolution::A_16X9_R_1280X720 };
        bool mMaximized{ false };
        bool mVSync{ false };
    };
}