#pragma once

#include "../Api.hpp"
#include "../Window/Window.hpp"
#include "GuiStyle.hpp"
#include "../../Config/ApplicationGuiConfiguration.hpp"

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

        XN_NODISCARD static std::unique_ptr<Gui> create(Window& window, 
            const GuiConfiguration& guiConfiguration);
    };
}
