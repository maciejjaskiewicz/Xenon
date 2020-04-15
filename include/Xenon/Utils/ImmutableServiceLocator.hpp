#pragma once

#include "Xenon/Core/Api.hpp"

#include <memory>

// For testing purpose
namespace XenonTest::Utils
{
    class Utils_ImmutableServiceLocatorTest;
}

namespace Xenon
{
    template<typename TService>
    struct ImmutableServiceLocator
    {
        ImmutableServiceLocator() = delete;
        ~ImmutableServiceLocator() = delete;

        static void set(std::shared_ptr<TService> servicePtr)
        {
            XN_ASSERT_COM(servicePtr, "Service pointer cannot be null");
            XN_ASSERT_COM(empty(), "Already initialized");

            sService = std::move(servicePtr);
        }

        template<typename TImpl = TService, typename... Args>
        static void createAndSet(Args&&... args)
        {
            XN_ASSERT_COM(empty(), "Already initialized");
            sService = std::make_shared<TImpl>(std::forward<Args>(args)...);
        }

        static std::shared_ptr<TService> get() noexcept
        {
            XN_ASSERT_COM(!empty(), "Tried to return a null shared_ptr");
            return sService;
        }

        static TService& ref() noexcept
        {
            XN_ASSERT_COM(!empty(), "Tried to return a nullptr reference");
            return *sService;
        }

        static void assertIsNotEmpty()
        {
            XN_ASSERT_COM(!empty(), "Uninitialized");
        }

    private:
        static bool empty() noexcept
        {
            return !sService;
        }

        static void reset() noexcept
        {
            sService.reset();
        }

        inline static std::shared_ptr<TService> sService = nullptr;

        // For testing purpose
        friend class XenonTest::Utils::Utils_ImmutableServiceLocatorTest;
    };
}