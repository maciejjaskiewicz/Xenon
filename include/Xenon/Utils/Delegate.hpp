#pragma once

#include "../Core/Api.hpp"

#include <type_traits>

namespace Xenon
{
    template<auto>
    struct BindDelegateArgT {};

    template<auto TFunc>
    constexpr BindDelegateArgT<TFunc> BIND_ARG{};

    template<typename> class Delegate;

    template<typename TReturn, typename... Args>
    class Delegate<TReturn(Args...)>
    {
    public:
        explicit Delegate() = default;

        template<auto TFunction>
        explicit Delegate(BindDelegateArgT<TFunction>) noexcept
            : Delegate{}
        {
            bind<TFunction>();
        }

        template<auto TFunction>
        void bind() noexcept
        {
            static_assert(std::is_invocable_r_v<TReturn, decltype(TFunction), Args...>);

            mFunction = [](Args... args) -> TReturn
            {
                return TReturn(std::invoke(TFunction, std::forward<Args>(args)...));
            };
        }

        XN_NODISCARD bool empty() const noexcept
        {
            return mFunction == nullptr;
        }

        void reset() noexcept
        {
            mFunction = nullptr;
        }

        TReturn operator()(Args... args) const
        {
            XN_ASSERT_COM(mFunction, "An unbinded function cannot be invoked");
            return mFunction(std::forward<Args>(args)...);
        }

        explicit operator bool() const noexcept
        {
            return !empty();
        }

        bool operator==(const Delegate<TReturn(Args...)>& other) const noexcept
        {
            return mFunction == other.mFunction;
        }

    private:
        using FnPrototype = TReturn(Args...);
        FnPrototype* mFunction{ nullptr };
    };

    template<typename... Args>
    using Action = Delegate<void(Args...)>;

    template<typename TReturn, typename... Args>
    using Func = Delegate<TReturn(Args...)>;
}