#include <gtest/gtest.h>

#include <vector>
#include <numeric>

TEST(Dummy, test_dummy)
{
    std::vector<int> values{ 1, 2, 3 };

    const auto sum = std::accumulate(values.begin(), values.end(), 0);

    EXPECT_EQ(sum, 6);
}