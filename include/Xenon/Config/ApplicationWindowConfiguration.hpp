#pragma once

#include "../Core/Api.hpp"
#include "../Core/Window/WindowResolution.hpp"

#include <string>

namespace Xenon
{
    
    class ApplicationWindowConfiguration
    {
    public:
        explicit ApplicationWindowConfiguration();

        void setTitle(const std::string& title);
        void setResolution(const WindowResolution& resolution);
        void maximize(bool maximize = true);
        void setVSync(bool enabled);

        XN_NODISCARD std::string getTitle() const;
        XN_NODISCARD WindowResolution getResolution() const;
        XN_NODISCARD bool isMaximized() const;
        XN_NODISCARD bool vSync() const;
    private:
        std::string mTitle{ "Xenon application" };
        WindowResolution mResolution{ StandardWindowResolution::A_16X9_R_1280X720 };
        bool mMaximized{ false };
        bool mVSync{ false };
    };
}