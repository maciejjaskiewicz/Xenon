#pragma once

namespace XenonTest::Utils
{
    class ITestService
    {
    public:
        virtual ~ITestService() = default;
        virtual bool test() = 0;
    };

    class TestService : public ITestService
    {
    public:
        TestService(const bool value)
            : mValue(value)
        { }

        bool test() override
        {
            return mValue;
        }
    private:
        bool mValue;
    };
}