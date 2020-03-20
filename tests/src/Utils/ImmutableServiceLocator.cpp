#include <gtest/gtest.h>

#include <Xenon/Utils/ImmutableServiceLocator.hpp>
#include "TestService.hpp"

namespace XenonTest::Utils
{
    class Utils_ImmutableServiceLocatorTest : public ::testing::Test
    {
    public:
        using TestServiceLocator = Xenon::ImmutableServiceLocator<ITestService>;

        static void TestServiceLocatorReset()
        {
            TestServiceLocator::reset();
        }

        static bool TestServiceLocatorEmpty() noexcept
        {
            return TestServiceLocator::empty();
        }
    };

    TEST_F(Utils_ImmutableServiceLocatorTest, should_set_without_exception)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        const auto service = std::make_shared<TestService>(true);

        EXPECT_NO_THROW(TestServiceLocator::set(service));
        EXPECT_FALSE(TestServiceLocatorEmpty());
    }

    TEST_F(Utils_ImmutableServiceLocatorTest, should_create_and_set_without_exception)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        EXPECT_NO_THROW(
            TestServiceLocator::createAndSet<TestService>(true)
        );
        EXPECT_FALSE(TestServiceLocatorEmpty());
    }

    TEST_F(Utils_ImmutableServiceLocatorTest, should_death_when_set_with_null_ptr)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        const auto nullService = std::shared_ptr<TestService>(nullptr);

        EXPECT_DEBUG_DEATH(TestServiceLocator::set(nullService), "");
    }

    TEST_F(Utils_ImmutableServiceLocatorTest, should_death_after_reinitialization_with_set)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        const auto service = std::make_shared<TestService>(true);
        TestServiceLocator::set(service);

        EXPECT_DEBUG_DEATH(TestServiceLocator::set(service), "");
    }

    TEST_F(Utils_ImmutableServiceLocatorTest, should_death_after_reinitialization_with_create_and_set)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        TestServiceLocator::createAndSet<TestService>(false);

        EXPECT_DEBUG_DEATH(TestServiceLocator::createAndSet<TestService>(false), "");
    }

    TEST_F(Utils_ImmutableServiceLocatorTest, get_method_should_return_non_empty_shared_ptr_after_set)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        const auto service = std::make_shared<TestService>(true);
        TestServiceLocator::set(service);

        const auto resolvedService = TestServiceLocator::get();

        EXPECT_TRUE(resolvedService);
        EXPECT_EQ(service, resolvedService);
    }

    TEST_F(Utils_ImmutableServiceLocatorTest, get_method_should_return_non_empty_shared_ptr_after_create_and_set)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        TestServiceLocator::createAndSet<TestService>(true);

        const auto resolvedService = TestServiceLocator::get();
        EXPECT_TRUE(resolvedService);
    }

    TEST_F(Utils_ImmutableServiceLocatorTest, get_method_should_death_without_initialization)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        EXPECT_DEBUG_DEATH(TestServiceLocator::get(), "");
    }

    TEST_F(Utils_ImmutableServiceLocatorTest, ref_method_should_death_without_initialization)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        EXPECT_DEBUG_DEATH(TestServiceLocator::ref(), "");
    }

    TEST_F(Utils_ImmutableServiceLocatorTest, assert_method_should_death_without_initialization)
    {
        TestServiceLocatorReset();
        ASSERT_TRUE(TestServiceLocatorEmpty());

        EXPECT_DEBUG_DEATH(TestServiceLocator::assertIsNotEmpty(), "");
    }
}