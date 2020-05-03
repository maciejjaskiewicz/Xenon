#pragma once

#include "GuiStyle.hpp"
#include "Xenon/Core/Api.hpp"
#include "Xenon/Core/Window/Window.hpp"
#include "Xenon/Config/ApplicationGuiConfiguration.hpp"

struct ImFont;

namespace Xenon
{
    struct GuiConfiguration
    {
        GuiStyle style{ GuiStyle::Classic };
        bool docking{ false };
        bool viewports{ false };

        explicit GuiConfiguration(const ApplicationGuiConfiguration& appGuiCfg)
            : style(appGuiCfg.style()), docking(appGuiCfg.docking()),
              viewports(appGuiCfg.viewports())
        { }
    };

    class Gui
    {
    public:
        virtual ~Gui() = default;

        virtual void init() = 0;
        virtual void newFrame() const = 0;
        virtual void render() const = 0;

        virtual void setFont(ImFont* font) = 0;

        XN_NODISCARD static std::unique_ptr<Gui> create(Window& window, 
            const GuiConfiguration& guiConfiguration);
    };
}
