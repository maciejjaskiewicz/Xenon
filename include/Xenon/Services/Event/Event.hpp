#pragma once

#include "../../Core/Api.hpp"

#include <typeindex>
#include <string>

namespace Xenon
{
    struct Event
    {
        virtual ~Event() = default;

        XN_NODISCARD virtual std::type_index typeIndex() const noexcept
        {
            return typeid(*this);
        }

        XN_NODISCARD virtual std::string toString() const
        {
            return typeid(*this).name();
        }
    };
}