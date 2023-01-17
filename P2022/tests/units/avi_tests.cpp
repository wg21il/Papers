#include "catch2/catch_all.hpp"

#include "3way.hpp"

#include <array>

TEST_CASE("test with default projections and compare function")
{
    // generating two lists, l1 and l2, where until the kth index they are identical and after it
    // each element in l2 is greater than l1 by one

    int n = 10;
    int k = static_cast<int>(0.75 * n);

    std::vector<int> l1{};
    l1.reserve(n);
    std::vector<int> l2{};
    l2.reserve(n);

    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    for (int i = 0; i < n; ++i)
    {
        int l1Elem = distrib(gen);
        int l2Elem = i < k ? l1Elem : l1Elem + 1;
        l1.push_back(l1Elem);
        l2.push_back(l2Elem);
    }

    auto res =
        std::ranges::lexicographical_compare_three_way(
            std::begin(l1), std::end(l1),
            std::begin(l2), std::end(l2)
        );

    CHECK(res == std::strong_ordering::less);
}

TEST_CASE("test with custom compare function")
{
    // generating two lists, l1 in small caps and l2 is big caps, 
    // which have the same words but in different order
    // using a comp function which is case INSENSETIVE

    std::vector<std::string> lowerCaseNums{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };
    std::vector<std::string> upperCaseNums{ "ONE", "FOUR" , "THREE", "TWO", "NINE", "EIGHT", "SEVEN", "SIX", "FIVE", "TEN" };

    auto caseInsensitiveCmp = [](std::string x, std::string y) -> std::strong_ordering
    {
        for (char& c : x)
        {
            c = std::toupper(c);
        }
        for (char& c : y)
        {
            c = std::toupper(c);
        }

        if (x < y)
        {
            return std::strong_ordering::less;
        }
        else if (x > y)
        {
            return std::strong_ordering::greater;
        }
        else
        {
            return std::strong_ordering::equal;
        }
    };

    auto res =
        std::ranges::lexicographical_compare_three_way(
            std::begin(lowerCaseNums), std::end(lowerCaseNums),
            std::begin(upperCaseNums), std::end(upperCaseNums),
            caseInsensitiveCmp
        );

    CHECK(res == std::strong_ordering::greater);
}

TEST_CASE("test with custom compare function which returns std::partial_ordering::unordered")
{
    // generating two lists, l1 and l2, where until the kth index they are identical and after it
    // each element in l2 an empty std::optional

    int n = 10;
    int k = static_cast<int>(0.75 * n);

    std::vector<std::optional<int>> l1{};
    l1.reserve(n);
    std::vector<std::optional<int>> l2{};
    l2.reserve(n);

    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution<> distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    for (int i = 0; i < n; ++i)
    {
        std::optional<int> l1Elem = distrib(gen);
        std::optional<int> l2Elem = i < k ? l1Elem : std::optional<int>{};
        l1.push_back(l1Elem);
        l2.push_back(l2Elem);
    }

    auto myCmp = [](const std::optional<int>& x, const std::optional<int>& y) -> std::partial_ordering
    {
        if (x && y)
        {
            std::strong_ordering so{ x <=> y };
            if (so < 0)
            {
                return std::partial_ordering::less;
            }
            else if (so > 0)
            {
                return std::partial_ordering::greater;
            }
            else
            {
                return std::partial_ordering::equivalent;
            }
        }
        else
        {
            return std::partial_ordering::unordered;
        }
    };

    auto res =
        std::ranges::lexicographical_compare_three_way(
            std::begin(l1), std::end(l1),
            std::begin(l2), std::end(l2),
            myCmp
        );

    CHECK(res == std::partial_ordering::unordered);
}

TEST_CASE("test with custom projections and custom compare function")
{
    // generating two lists, l1 and l2, where the elements of l2 are twice as big
    // as the elements in l1
    // with two different projects
    // l1's projection will multiply its elements by 6 and add one
    // l2's projection will multiply its element by 3 and subtract one
    // the comp function will subtract one from l1 and
    // add one to l2, and then 3-way compare them

    constexpr std::size_t n{ 10U };

    std::array<int, n> l1{};
    std::array<int, n> l2{};

    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    for (int i = 0; i < n; ++i)
    {
        int elem = distrib(gen);
        l1[i] = elem;
        l2[i] = 2 * elem;
    }

    auto l1Proj = [](int l1Elem) { return 6 * l1Elem + 1; };
    auto l2Proj = [](int l2Elem) { return 3 * l2Elem - 1; };

    auto cmp = [](int l1Elem, int l2Elem) { return --l1Elem <=> ++l2Elem; };

    auto res =
        std::ranges::lexicographical_compare_three_way(
            std::begin(l1), std::end(l1),
            std::begin(l2), std::end(l2),
            cmp,
            l1Proj,
            l2Proj
        );

    CHECK(res == std::strong_ordering::equal);
}