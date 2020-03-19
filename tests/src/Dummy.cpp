#include <catch2/catch.hpp>

#include <vector>
#include <numeric>

TEST_CASE("Dummy")
{
    std::vector<int> values{ 1, 2, 3 };

    const auto sum = std::accumulate(values.begin(), values.end(), 0);

    REQUIRE(sum == 6);
}