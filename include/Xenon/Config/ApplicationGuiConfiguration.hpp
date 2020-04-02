#pragma once

#include "../Core/Api.hpp"
#include "../Core/Gui/GuiStyle.hpp"

namespace Xenon
{
    class ApplicationGuiConfiguration
    {
    public:
        explicit ApplicationGuiConfiguration();

        void setStyle(GuiStyle style) noexcept;
        void useDocking() noexcept;
        void useViewports() noexcept;

        XN_NODISCARD GuiStyle style() const noexcept;
        XN_NODISCARD bool docking() const noexcept;
        XN_NODISCARD bool viewports() const noexcept;
    private:
        GuiStyle mStyle{ GuiStyle::Classic };
        bool mDocking{ false };
        bool mViewports{ false };
    };
}