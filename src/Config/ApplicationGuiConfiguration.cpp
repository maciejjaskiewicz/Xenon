#include <Config/ApplicationGuiConfiguration.hpp>

namespace Xenon
{
    ApplicationGuiConfiguration::ApplicationGuiConfiguration() = default;

    void ApplicationGuiConfiguration::setStyle(const GuiStyle style) noexcept
    {
        mStyle = style;
    }

    void ApplicationGuiConfiguration::useDocking() noexcept
    {
        mDocking = true;
    }

    void ApplicationGuiConfiguration::useViewports() noexcept
    {
        mViewports = true;
    }

    XN_NODISCARD GuiStyle ApplicationGuiConfiguration::style() const noexcept
    {
        return mStyle;
    }

    XN_NODISCARD bool ApplicationGuiConfiguration::docking() const noexcept
    {
        return mDocking;
    }

    XN_NODISCARD bool ApplicationGuiConfiguration::viewports() const noexcept
    {
        return mViewports;
    }
}
