#pragma once

#include <memory>
#include <stdexcept>

namespace Xenon
{
    template<typename TService>
    struct ServiceLocator
    {
        ServiceLocator() = delete;
        ~ServiceLocator() = delete;

        static void set(std::shared_ptr<TService> servicePtr)
        {
            if(!servicePtr)
            {
                throw std::invalid_argument(
                    "Service pointer cannot be null");
            }

            sService = std::move(servicePtr);
        }

        template<typename TImpl = TService, typename... Args>
        static void createAndSet(Args&&... args)
        {
            sService = std::make_shared<TImpl>(std::forward<Args>(args)...);
        }

        static std::weak_ptr<TService> get() noexcept
        {
            return sService;
        }

        static TService& ref()
        {
            if (empty())
            {
                throw std::runtime_error(
                    "Tried to return a nullptr reference");
            }

            return *sService;
        }

        static bool empty() noexcept
        {
            return !sService;
        }

        static void reset() noexcept
        {
            sService.reset();
        }

    private:
        inline static std::shared_ptr<TService> sService = nullptr;
    };
}