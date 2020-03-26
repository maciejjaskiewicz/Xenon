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

    void ApplicationWindowConfiguration::setResolution(const WindowResolution& resolution)
    {
        mResolution = resolution;
    }

    void ApplicationWindowConfiguration::maximize(const bool maximize)
    {
        mMaximized = maximize;
    }

    void ApplicationWindowConfiguration::setVSync(const bool enabled)
    {
        mVSync = enabled;
    }

    std::string ApplicationWindowConfiguration::getTitle() const
    {
        return mTitle;
    }

    WindowResolution ApplicationWindowConfiguration::getResolution() const
    {
        return mResolution;
    }

    bool ApplicationWindowConfiguration::isMaximized() const
    {
        return mMaximized;
    }

    bool ApplicationWindowConfiguration::vSync() const
    {
        return mVSync;
    }
}
