#include <gtest/gtest.h>

#include <Xenon/Utils/ServiceLocator.hpp>
#include "TestService.hpp"

namespace XenonTest::Utils
{
    TEST(Utils_ServiceLocator_Test, should_set_without_exception)
    {
        Xenon::ServiceLocator<ITestService>::reset();
        ASSERT_TRUE(Xenon::ServiceLocator<ITestService>::empty());

        const auto service = std::make_shared<TestService>(true);

        EXPECT_NO_THROW(Xenon::ServiceLocator<ITestService>::set(service));
        EXPECT_FALSE(Xenon::ServiceLocator<ITestService>::empty());
    }

    TEST(Utils_ServiceLocator_Test, should_create_and_set_without_exception)
    {
        Xenon::ServiceLocator<ITestService>::reset();
        ASSERT_TRUE(Xenon::ServiceLocator<ITestService>::empty());

        EXPECT_NO_THROW(
            Xenon::ServiceLocator<ITestService>::createAndSet<TestService>(true)
        );
        EXPECT_FALSE(Xenon::ServiceLocator<ITestService>::empty());
    }

    TEST(Utils_ServiceLocator_Test, should_throw_when_set_with_null_ptr)
    {
        Xenon::ServiceLocator<ITestService>::reset();
        ASSERT_TRUE(Xenon::ServiceLocator<ITestService>::empty());

        const auto nullService = std::shared_ptr<TestService>(nullptr);

        EXPECT_THROW(
            Xenon::ServiceLocator<ITestService>::set(nullService),
            std::invalid_argument
        );
    }

    TEST(Utils_ServiceLocator_Test, should_reset_serive_locator)
    {
        Xenon::ServiceLocator<ITestService>::reset();
        ASSERT_TRUE(Xenon::ServiceLocator<ITestService>::empty());

        Xenon::ServiceLocator<ITestService>::createAndSet<TestService>(true);
        EXPECT_FALSE(Xenon::ServiceLocator<ITestService>::empty());

        Xenon::ServiceLocator<ITestService>::reset();

        EXPECT_TRUE(Xenon::ServiceLocator<ITestService>::empty());
    }

    TEST(Utils_ServiceLocator_Test, get_method_should_return_non_empty_weak_ptr_after_set)
    {
        Xenon::ServiceLocator<ITestService>::reset();
        ASSERT_TRUE(Xenon::ServiceLocator<ITestService>::empty());

        const auto service = std::make_shared<TestService>(true);
        Xenon::ServiceLocator<ITestService>::set(service);

        const auto resolvedService = Xenon::ServiceLocator<ITestService>::get();
        EXPECT_FALSE(resolvedService.expired());
        EXPECT_EQ(service, resolvedService.lock());
    }

    TEST(Utils_ServiceLocator_Test, get_method_should_return_non_empty_weak_ptr_after_create_and_set)
    {
        Xenon::ServiceLocator<ITestService>::reset();
        ASSERT_TRUE(Xenon::ServiceLocator<ITestService>::empty());

        Xenon::ServiceLocator<ITestService>::createAndSet<TestService>(true);

        const auto resolvedService = Xenon::ServiceLocator<ITestService>::get();
        EXPECT_FALSE(resolvedService.expired());
    }

    TEST(Utils_ServiceLocator_Test, get_method_should_return_empty_weak_ptr)
    {
        Xenon::ServiceLocator<ITestService>::reset();
        ASSERT_TRUE(Xenon::ServiceLocator<ITestService>::empty());

        const auto resolvedService = Xenon::ServiceLocator<ITestService>::get();
        EXPECT_TRUE(resolvedService.expired());
    }

    TEST(Utils_ServiceLocator_Test, after_set_ref_method_should_return_reference_without_exception)
    {
        Xenon::ServiceLocator<ITestService>::reset();
        ASSERT_TRUE(Xenon::ServiceLocator<ITestService>::empty());

        const auto service = std::make_shared<TestService>(true);
        Xenon::ServiceLocator<ITestService>::set(service);

        EXPECT_NO_THROW(Xenon::ServiceLocator<ITestService>::ref());
    }

    TEST(Utils_ServiceLocator_Test, when_not_set_ref_method_should_throw)
    {
        Xenon::ServiceLocator<ITestService>::reset();
        ASSERT_TRUE(Xenon::ServiceLocator<ITestService>::empty());

        EXPECT_THROW(
            Xenon::ServiceLocator<ITestService>::ref(),
            std::runtime_error
        );
    }
}