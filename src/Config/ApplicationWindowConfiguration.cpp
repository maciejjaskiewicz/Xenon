#include <Xenon/Config/ApplicationWindowConfiguration.hpp>

namespace Xenon
{
    ApplicationWindowConfiguration::ApplicationWindowConfiguration()
    {
        mResolution = WindowResolution();
    }

    void ApplicationWindowConfiguration::setTitle(const std::string& title)
    {
        mTitle = title;
    }

    void ApplicationWindowConfiguration::setResolution(const WindowResolution& resolution) noexcept
    {
        mResolution = resolution;
    }

    void ApplicationWindowConfiguration::maximize(const bool maximize) noexcept
    {
        mMaximized = maximize;
    }

    void ApplicationWindowConfiguration::setVSync(const bool enabled) noexcept
    {
        mVSync = enabled;
    }

    std::string ApplicationWindowConfiguration::title() const
    {
        return mTitle;
    }

    WindowResolution ApplicationWindowConfiguration::resolution() const
    {
        return mResolution;
    }

    bool ApplicationWindowConfiguration::maximized() const
    {
        return mMaximized;
    }

    bool ApplicationWindowConfiguration::vSync() const
    {
        return mVSync;
    }
}
