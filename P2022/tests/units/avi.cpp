#include <numeric>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <algorithm>
#include <functional>
#include <optional>
#include <cassert>
#include <format>
#include <random>
#include <limits>


using namespace std;


std::pair<std::vector<int>, std::vector<int>> generateFirstExample(int n, int k, int diff)
{
    assert(k < n);

    std::vector<int> l1{};
    l1.reserve(n);
    std::vector<int> l2{};
    l2.reserve(n);

    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution<> distrib(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    for (int i = 0; i < n; ++i)
    {
        int l1Elem = distrib(gen);
        int l2Elem = i < k ? l1Elem : l1Elem + diff;
        l1.push_back(l1Elem);
        l2.push_back(l2Elem);
    }
    
    return { l1, l2 };
}


void printResultStrongOrdering(std::string_view s1, std::string_view s2, std::strong_ordering o)
{
    std::cout << std::quoted(s1) << " is ";
    if (o < 0)
    {
        std::cout << "less than ";
    }
    else if (o > 0)
    {
        std::cout << "greater than ";
    }
    else if (o == 0)
    {
        std::cout << "equal to ";
    }
    else
    {
        std::cout << "unordered to ";
    }
    std::cout << std::quoted(s2) << '\n';
}

void printFirstExample()
{
    int n = 10;
    int k = static_cast<int>(0.75 * n);
    auto [l1, l2] = generateFirstExample(n, k, 1);
    for (int i = 0; i < n; ++i)
    {
        printResultStrongOrdering(std::to_string(l1[i]), std::to_string(l2[i]), l1[i] <=> l2[i]);
    }
    std::cout << '\n';
}

std::pair<std::vector<std::string_view>, std::vector<std::string_view>> generateSecondExample()
{
    std::vector<std::string_view> lowerCaseNums{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };
    std::vector<std::string_view> upperCaseNums{ "ONE", "FOUR" , "THREE", "TWO", "NINE", "EIGHT", "SEVEN", "SIX", "FIVE", "TEN" };
    return { lowerCaseNums, upperCaseNums };
}

void printSecondExample()
{
    auto caseInsensitiveCmp = [](string&& x, string&& y)
    {
        for (char& c : x)
            c = std::toupper(c);
        for (char& c : y)
            c = std::toupper(c);

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

    auto [l1, l2] = generateSecondExample();
    for (int i = 0; i < ssize(l1); ++i)
    {
        printResultStrongOrdering(l1[i], l2[i], caseInsensitiveCmp(std::string{ l1[i] }, std::string{ l2[i] }));
    }
    std::cout << '\n';
}

void printResultPartialOrdering(std::string_view s1, std::string_view s2, std::partial_ordering o)
{
    std::cout << std::quoted(s1) << " is ";
    if (o < 0)
    {
        std::cout << "less than ";
    }
    else if (o > 0)
    {
        std::cout << "greater than ";
    }
    else if (o == 0)
    {
        std::cout << "equal to ";
    }
    else
    {
        std::cout << "unordered to ";
    }
    std::cout << std::quoted(s2) << '\n';
}

std::pair<std::vector<std::optional<int>>, std::vector<std::optional<int>>> generateThirdExample(int n, int k)
{
    assert(k < n);

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

    return { l1, l2 };
}

void printThirdExample()
{
    auto myCmp = [](const std::optional<int>& x, const std::optional<int>& y)
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

    auto myToStr = [](const std::optional<int>& x) -> string
    {
        if (x)
        {
            return std::to_string(*x);
        }
        else
        {
            return "";
        }
    };

    int n = 10;
    int k = static_cast<int>(0.75 * n);
    auto [l1, l2] = generateThirdExample(n, k);
    for (int i = 0; i < n; ++i)
    {
        printResultPartialOrdering(myToStr(l1[i]), myToStr(l2[i]), myCmp(l1[i], l2[i]));
    }
    std::cout << '\n';
}

void printFourthExample()
{
    auto f = [](double x) -> double { return x * x; };
    auto g = [](double y) -> double { return (y * 1.00001) * (y * 1.00001); };


    auto myComp = [](double x, double y, double fx, double gy)
    {
        static int sigma = 5;

        // abs(x - y) > sigma               are unordered
        // f(x) == g(y)                     are equal
        // abs(f(x) - g(y)) < eps           are equivalent
        // f(x) < g(y)                      are lesser
        // f(x) > g(y)                      are greater

        if (abs(x - y) > sigma)
        {
            return std::partial_ordering::unordered;
        }
        else
        {
            static double eps = 0.5;

            if (std::abs(fx - gy) < eps)
            {
                return std::partial_ordering::equivalent;
            }
            else if (fx < gy)
            {
                return std::partial_ordering::less;
            }
            else
            {
                return std::partial_ordering::greater;
            }
        }
    };

    int n = 10;
    int k = static_cast<int>(0.75 * n);
    std::vector<double> l1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<double> l2{ 0.1, 1.2, 3.3, 4.4, 5.5, 6.6, 7.7, 11.1, 18.3, 20.6, };
    for (int i = 0; i < n; ++i)
    {
        double fx = f(l1[i]);
        double gy = g(l2[i]);

        printResultPartialOrdering(std::to_string(fx), std::to_string(gy), myComp(l1[i], l2[i], fx, gy));
    }
    std::cout << '\n';
}

int main()
{
    cout << "Hello World\n";

    printFirstExample();

    printSecondExample();

    printThirdExample();

    printFourthExample();

    return EXIT_SUCCESS;
}

/*
template<
    input_iterator I1, sentinel_for<I1> S1,
    input_iterator I2, sentinel_for<I2> S2,
    class Proj1 = identity, 
    class Proj2 = identity,
    class Comp = compare_three_way
>
requires
    three_way_comparable_with< 
        projected<I1,Proj1>, projected<I2,Proj2> 
    >
constexpr auto
    ranges::lexicographical_compare_three_way( 
        I1 first1, S1 last1, I2 first2, S2 last2, Comp comp = {}, Proj1 = {}, Proj2 = {}
    ) -> std::common_comparison_category_t<
				// TODO: need to use projections!!!
                decltype(comp(*first1, *first2)), std::strong_ordering>;

*/
