#include <gtest/gtest.h>

#include <Xenon/Utils/Delegate.hpp>
#include <string>

namespace XenonTest::Utils
{
    void testFunctionVoid(int& i)
    {
        i++;
    }

    std::string testFunctionReturn(const int i)
    {
        return std::to_string(i);
    }

    TEST(Utils_Delegate_Test, should_create_empty_action)
    {
        const Xenon::Action<int&> actionDelegate{};
        ASSERT_TRUE(actionDelegate.empty());
    }

    TEST(Utils_Delegate_Test, should_create_empty_func)
    {
        const Xenon::Func<std::string, int> funcDelegate{};
        ASSERT_TRUE(funcDelegate.empty());
    }

    TEST(Utils_Delegate_Test, action_should_bind)
    {
        Xenon::Action<int&> actionDelegate{};
        ASSERT_TRUE(actionDelegate.empty());

        actionDelegate.bind<&testFunctionVoid>();
        EXPECT_FALSE(actionDelegate.empty());
    }

    TEST(Utils_Delegate_Test, func_should_bind)
    {
        Xenon::Func<std::string, int> funcDelegate{};
        ASSERT_TRUE(funcDelegate.empty());

        funcDelegate.bind<&testFunctionReturn>();
        EXPECT_FALSE(funcDelegate.empty());
    }

    TEST(Utils_Delegate_Test, bool_operator_should_return_false_when_empty)
    {
        const Xenon::Action<int&> actionDelegate{};
        EXPECT_FALSE(actionDelegate);
    }

    TEST(Utils_Delegate_Test, bool_operator_should_return_true_when_binded)
    {
        Xenon::Action<int&> actionDelegate{};
        ASSERT_FALSE(actionDelegate);

        actionDelegate.bind<&testFunctionVoid>();
        EXPECT_TRUE(actionDelegate);
    }

    TEST(Utils_Delegate_Test, action_should_bind_with_constructor)
    {
        const Xenon::Action<int&> actionDelegate{ Xenon::BIND_ARG<&testFunctionVoid> };
        EXPECT_TRUE(actionDelegate);
    }

    TEST(Utils_Delegate_Test, func_should_bind_with_constructor)
    {
        const Xenon::Func<std::string, int> funcDelegate{ Xenon::BIND_ARG<&testFunctionReturn> };
        EXPECT_TRUE(funcDelegate);
    }

    TEST(Utils_Delegate_Test, action_should_invoke_function)
    {
        const Xenon::Action<int&> actionDelegate{ Xenon::BIND_ARG<&testFunctionVoid> };
        ASSERT_TRUE(actionDelegate);

        auto test = 0;
        EXPECT_NO_FATAL_FAILURE(actionDelegate(test));
        EXPECT_EQ(test, 1);
    }

    TEST(Utils_Delegate_Test, func_should_invoke_function)
    {
        const Xenon::Func<std::string, int> funcDelegate{ Xenon::BIND_ARG<&testFunctionReturn> };
        ASSERT_TRUE(funcDelegate);

        auto result = std::string("");
        EXPECT_NO_FATAL_FAILURE({ result = funcDelegate(1); });
        EXPECT_EQ(result, "1");
    }

    TEST(Utils_Delegate_Test, action_should_death_when_unbinded)
    {
        const Xenon::Action<int&> actionDelegate{};
        ASSERT_FALSE(actionDelegate);

        auto test = 0;
        EXPECT_DEATH(actionDelegate(test), "");
    }

    TEST(Utils_Delegate_Test, func_should_death_when_unbinded)
    {
        const Xenon::Func<std::string, int> funcDelegate{};
        ASSERT_FALSE(funcDelegate);

        auto result = std::string("");
        EXPECT_DEATH({ result = funcDelegate(1); }, "");
    }

    TEST(Utils_Delegate_Test, actions_binded_with_the_same_function_should_be_equal)
    {
        const Xenon::Action<int&> actionDelegate1{ Xenon::BIND_ARG<&testFunctionVoid> };
        ASSERT_TRUE(actionDelegate1);

        const Xenon::Action<int&> actionDelegate2{ Xenon::BIND_ARG<&testFunctionVoid> };
        ASSERT_TRUE(actionDelegate2);

        EXPECT_EQ(actionDelegate1, actionDelegate2);
    }

    TEST(Utils_Delegate_Test, funcs_binded_with_the_same_function_should_be_equal)
    {
        const Xenon::Func<std::string, int> funcDelegate1{ Xenon::BIND_ARG<&testFunctionReturn> };
        ASSERT_TRUE(funcDelegate1);

        const Xenon::Func<std::string, int> funcDelegate2{ Xenon::BIND_ARG<&testFunctionReturn> };
        ASSERT_TRUE(funcDelegate2);

        EXPECT_EQ(funcDelegate1, funcDelegate2);
    }

    TEST(Utils_Delegate_Test, action_should_bind_to_lambda)
    {
        Xenon::Action<int&> actionDelegate{};
        ASSERT_FALSE(actionDelegate);

        actionDelegate.bind([](int& i)
        {
            i++;    
        });

        auto test = 0;
        EXPECT_NO_FATAL_FAILURE(actionDelegate(test));
        EXPECT_EQ(test, 1);
    }

    TEST(Utils_Delegate_Test, func_should_bind_to_lambda)
    {
        Xenon::Func<std::string, int> funcDelegate{};
        ASSERT_FALSE(funcDelegate);

        funcDelegate.bind([](int i) -> std::string
        {
            return std::to_string(i);
        });

        auto result = std::string("");
        EXPECT_NO_FATAL_FAILURE({ result = funcDelegate(1); });
        EXPECT_EQ(result, "1");
    }

    TEST(Utils_Delegate_Test, copy_of_delegate_should_invoke)
    {
        Xenon::Action<int&> actionDelegate{};
        ASSERT_FALSE(actionDelegate);

        actionDelegate.bind([](int& i)
        {
            i++;
        });

        const auto actionDelegateCopy = actionDelegate;

        auto test = 0;
        EXPECT_NO_FATAL_FAILURE(actionDelegateCopy(test));
        EXPECT_EQ(test, 1);
    }

    TEST(Utils_Delegate_Test, action_should_bind_to_member_function)
    {
        Xenon::Action<int&> actionDelegate{};
        ASSERT_FALSE(actionDelegate);

        struct TestStruct
        {
            void test(int& i)
            {
                i++;
            }
        };

        TestStruct instance{};
        actionDelegate.bind<&TestStruct::test>(&instance);

        auto test = 0;
        EXPECT_NO_FATAL_FAILURE(actionDelegate(test));
        EXPECT_EQ(test, 1);
    }

    TEST(Utils_Delegate_Test, func_should_bind_to_member_function)
    {
        Xenon::Func<std::string, int> funcDelegate{};
        ASSERT_FALSE(funcDelegate);

        struct TestStruct
        {
            std::string test(int i)
            {
                return std::to_string(i);
            }
        };

        TestStruct instance{};
        funcDelegate.bind<&TestStruct::test>(&instance);

        auto result = std::string("");
        EXPECT_NO_FATAL_FAILURE({ result = funcDelegate(1); });
        EXPECT_EQ(result, "1");
    }
}