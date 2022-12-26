

//#include <concepts>
#include <iterator>
#include <compare>

namespace std::ranges
{


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
    lexicographical_compare_three_way( 
        I1 first1, 
        S1 last1, 
        I2 first2, 
        S2 last2, 
        Comp comp = {}, 
        Proj1 proj1 = {}, 
        Proj2 proj2 = {}
    ) -> common_comparison_category_t<
                decltype(
                        comp(proj1(*first1), proj2(*first2))), 
                        strong_ordering
                >
{
    return strong_ordering::equal;
}

}

