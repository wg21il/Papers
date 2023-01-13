

#include "catch2/catch_all.hpp"

template<
    typename T,
    class Comp = std::compare_three_way,
    class Proj = std::identity
>
requires 
    std::same_as<std::invoke_result_t<Comp,T,T>, std::strong_ordering> ||
    std::same_as<std::invoke_result_t<Comp,T,T>, std::weak_ordering> ||
    std::same_as<std::invoke_result_t<Comp,T,T>, std::partial_ordering>
auto foo(
        T t1, 
        T t2, 
        Comp f = {},
        Proj p = {}
    ) -> 
    std::common_comparison_category_t<
        decltype(std::invoke(f, t1, t2)), std::strong_ordering>
{
    return std::invoke(f, t1, t2);
}

struct goo
{
    template<typename T>
    auto operator()(T x, T y) -> std::partial_ordering
    {
        return std::partial_ordering::less;
    }
};
    

TEST_CASE("basic_check")
{
    double d = 1;
    foo(d, d);
    //foo(d, d, std::compare_three_way{});

    CHECK(true);
}
