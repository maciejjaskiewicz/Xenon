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
        Delegate() = default;

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

            reset();

            mFunction = [](StorageType&, Args... args) -> TReturn
            {
                return TReturn(std::invoke(TFunction, std::forward<Args>(args)...));
            };
        }

        template<typename TInvokable>
        void bind(TInvokable invokable)
        {
            static_assert(std::is_class_v<TInvokable>);
            static_assert(std::is_trivially_destructible_v<TInvokable>);
            static_assert(std::is_invocable_r_v<TReturn, TInvokable, Args...>);

            reset();
            new (&mStorage) TInvokable{ std::move(invokable) };

            mFunction = [](StorageType& storage, Args... args) -> TReturn
            {
                TInvokable& invokable = *reinterpret_cast<TInvokable*>(&storage);
                return std::invoke(invokable, args...);
            };
        }

        template<auto TCandidate, typename TInstance>
        void bind(TInstance instance)
        {
            static_assert(std::is_trivially_copyable_v<TInstance> && std::is_trivially_destructible_v<TInstance>);
            static_assert(std::is_invocable_r_v<TReturn, decltype(TCandidate), TInstance&, Args...>);

            reset();
            new (&mStorage) TInstance{ instance };

            mFunction = [](StorageType& storage, Args... args) -> TReturn
            {
                TInstance instance = *reinterpret_cast<TInstance*>(&storage);
                return std::invoke(TCandidate, instance, args...);
            };
        }

        XN_NODISCARD bool empty() const noexcept
        {
            return mFunction == nullptr;
        }

        void reset() noexcept
        {
            new (&mStorage) void* { nullptr };
            mFunction = nullptr;
        }

        TReturn operator()(Args... args) const
        {
            XN_ASSERT_COM(mFunction, "An unbinded function cannot be invoked");
            return mFunction(mStorage, std::forward<Args>(args)...);
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
        using StorageType = std::aligned_storage_t<sizeof(void*), alignof(void*)>;
        using FnPrototype = TReturn(StorageType&, Args...);

        mutable StorageType mStorage{};
        FnPrototype* mFunction{ nullptr };
    };

    template<typename... Args>
    using Action = Delegate<void(Args...)>;

    template<typename TReturn, typename... Args>
    using Func = Delegate<TReturn(Args...)>;
}