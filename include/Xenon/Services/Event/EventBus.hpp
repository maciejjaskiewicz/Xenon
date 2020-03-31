#pragma once

#include "EventSubject.hpp"

#include <memory>
#include <map>
#include <queue>

namespace Xenon
{
    class EventBus
    {
    public:
        template<typename TEvent, auto TListener>
        void subscribe()
        {
            static_assert(std::is_base_of<Event, TEvent>::value);
            provideSubject<TEvent>()->template addListener<TListener>();
        }

        template<typename TEvent, auto TMemberListener, typename TInstance>
        void subscribe(TInstance&& instance)
        {
            static_assert(std::is_base_of<Event, TEvent>::value);
            provideSubject<TEvent>()->template addListener<TMemberListener, TInstance>(std::forward<TInstance>(instance));
        }

        template<typename TEvent, typename TInvokable>
        void subscribe(TInvokable&& invokable)
        {
            static_assert(std::is_base_of<Event, TEvent>::value);
            provideSubject<TEvent>()->template addListener<TInvokable>(std::forward<TInvokable>(invokable));
        }

        template<typename TEvent, typename... Args>
        void trigger(Args&&... args)
        {
            static_assert(std::is_base_of<Event, TEvent>::value);

            const TEvent event{ std::forward<Args>(args)... };
            const auto idx = static_cast<const Event*>(&event)->typeIndex();

            publish(idx, event);
        }

        template<typename TEvent>
        void trigger(TEvent&& event)
        {
            static_assert(std::is_base_of<Event, std::decay_t<TEvent>>::value);

            const auto idx = static_cast<const Event*>(&event)->typeIndex();
            publish(idx, std::forward<TEvent>(event));
        }

        template<typename TEvent, typename... Args>
        void enqueue(Args&&... args)
        {
            static_assert(std::is_base_of<Event, TEvent>::value);

            auto event = std::make_unique<TEvent>(std::forward<Args>(args)...);
            mQueuedEvents.emplace(std::move(event));
        }

        template<typename TEvent>
        void enqueue(TEvent&& event)
        {
            static_assert(std::is_base_of<Event, std::decay_t<TEvent>>::value);

            auto eventPtr = std::make_unique<std::decay_t<TEvent>>(std::forward<TEvent>(event));
            mQueuedEvents.emplace(std::move(eventPtr));
        }

        void update()
        {
            while (!mQueuedEvents.empty())
            {
                const auto& event = mQueuedEvents.front();
                const auto idx = event->typeIndex();

                publish(idx, *event);
                mQueuedEvents.pop();
            }
        }

    private:
        template<typename TEvent>
        EventSubject<TEvent>* provideSubject()
        {
            const std::type_index idx = typeid(TEvent);
            auto eventSubjectIterator{ mSubjects.find(idx) };

            // Create a new event subject if was not found
            if (eventSubjectIterator == std::end(mSubjects))
            {
                auto eventSubject = std::make_unique<EventSubject<TEvent>>();
                eventSubjectIterator = mSubjects.emplace(idx, std::move(eventSubject)).first;
            }

            return static_cast<EventSubject<TEvent>*>(eventSubjectIterator->second.get());
        }

        void publish(const std::type_index& idx, const Event& event) const
        {
            //XN_ENG_TRACE(event.toString());

            const auto eventSubjectIterator{ mSubjects.find(idx) };

            if (eventSubjectIterator == std::end(mSubjects))
            {
                return;
            }

            eventSubjectIterator->second->publish(event);
        }

        std::map<std::type_index, std::unique_ptr<IEventSubject>> mSubjects;
        std::queue<std::unique_ptr<Event>> mQueuedEvents;
    };
}
