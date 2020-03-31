#include <Xenon/Core/Input/Input.hpp>

#include "../../Platform/Common/CommonInput.hpp"

namespace Xenon
{
    XN_NODISCARD std::unique_ptr<Input> Input::create(Window& window)
    {
        return std::make_unique<CommonInput>(window);
    }
}
