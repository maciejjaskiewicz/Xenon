#pragma once

#include "Event.hpp"
#include "../../Core/Api.hpp"
#include "../../Utils/Delegate.hpp"

#include <vector>
#include <utility>

namespace Xenon
{
    struct IEventSubject
    {
        virtual ~IEventSubject() = default;

        virtual void publish(const Event& event) const = 0;
        XN_NODISCARD virtual bool empty() const noexcept = 0;
        XN_NODISCARD virtual std::size_t size() const = 0;
    };

    template<typename TEvent>
    struct EventSubject final : IEventSubject
    {
        template<auto TListener>
        void addListener()
        {
            ListenerType listenerDelegate{};
            listenerDelegate.template bind<TListener>();

            mListeners.emplace_back(std::move(listenerDelegate));
        }

        template<auto TMemberListener, typename TInstance>
        void addListener(TInstance&& instance)
        {
            ListenerType listenerDelegate{};
            listenerDelegate.template bind<TMemberListener>(std::forward<TInstance>(instance));

            mListeners.emplace_back(std::move(listenerDelegate));
        }

        template<typename TInvokable>
        void addListener(TInvokable&& invokable)
        {
            ListenerType listenerDelegate{};
            listenerDelegate.bind(std::forward<TInvokable>(invokable));

            mListeners.emplace_back(std::move(listenerDelegate));
        }

        void publish(const Event& event) const override
        {
            for (auto&& listener : std::as_const(mListeners))
            {
                listener(static_cast<const TEvent&>(event));
            }
        }

        XN_NODISCARD bool empty() const noexcept override
        {
            return mListeners.empty();
        }

        XN_NODISCARD std::size_t size() const override
        {
            return mListeners.size();
        }

    private:
        using ListenerType = Action<const TEvent&>;
        std::vector<ListenerType> mListeners;
    };
}
