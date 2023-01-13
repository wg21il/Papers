

#include "catch2/catch_all.hpp"

using namespace std;

template<
    input_iterator F1,
    input_iterator L1,
    input_iterator F2,
    input_iterator L2,
    class Comp = compare_three_way,
    class Proj1 = identity,
    class Proj2 = identity
>
requires 
    same_as<invoke_result_t<Comp, invoke_result_t<Proj1, F1>, invoke_result_t<Proj2, F2>>, strong_ordering> ||
    same_as<invoke_result_t<Comp, invoke_result_t<Proj1, F1>, invoke_result_t<Proj2, F2>>, weak_ordering> ||
    same_as<invoke_result_t<Comp, invoke_result_t<Proj1, F1>, invoke_result_t<Proj2, F2>>, partial_ordering>
auto compare(
        F1 f1, L1 l1,
        F2 f2, L2 l2,
        Comp comp = {},
        Proj1 p1 = {},
        Proj2 p2 = {}
    ) -> 
    common_comparison_category_t<
        decltype(
                invoke(comp, invoke(p1,*f1), invoke(p2,*f2))), strong_ordering>
{
    while (f1 != l1)
    {
        if (f2 == l2)
        {
            return strong_ordering::greater;
        }

        if (
            auto cmp = comp(invoke(p1, *f1), invoke(p2, *f2));
            cmp != 0 
        ) 
        {
            return cmp;
        }

        ++f1;
        ++f2;
    }

    // GCC 11 implementation with the
    // note: See PR 94006
    return (f2 == l2) <=> true; 
}

struct goo
{
    template<typename T, typename U = T>
    auto operator()(T t, U u) -> partial_ordering
    {

        static_assert(std::same_as<T,int>);
        static_assert(std::same_as<U,char>);

        int char_as_int = static_cast<int>(u);
        if (char_as_int < 10)
        {
            return char_as_int <=> t;
        }
        else
        {
            return partial_ordering::unordered;
        }
    }

    /*
    auto operator()(int t, char u) -> partial_ordering
    {
        return partial_ordering::less;
    }
    */
};
    

TEST_CASE("basic_check")
{
    vector<int>  v1{1,2,3,4};
    vector<char> v2{'a', 'b'};

    compare(
            v1.begin(), v1.end(),
            v2.begin(), v2.end(),
            goo{}
           ); 
}
