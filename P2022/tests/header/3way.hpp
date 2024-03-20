

#include <iterator>
#include <ranges>
#include <concepts>


namespace std 
{
    template <
        typename T, 
        typename... U
    >
    concept same_as_any_of = (std::same_as<T, U> or ...); // exposition only
}

namespace std::ranges
{
    template<
        input_iterator I1,
        input_iterator I2,
        class Comp,
        class Proj1,
        class Proj2
    >

    using three_way_comparator_result_t =
        invoke_result_t<
            Comp&,
            typename projected<I1, Proj1>::value_type,
            typename projected<I2, Proj2>::value_type
        >; // exposition-only

    template<
            std::input_iterator I1,
            std::input_iterator I2,
            class Comp,
            class Proj1,
            class Proj2
    >
    constexpr bool is_three_way_ordering =
            std::same_as_any_of<
                three_way_comparator_result_t<I1, I2, Comp, Proj1, Proj2>,
                std::strong_ordering,
                std::weak_ordering,
                std::partial_ordering>; //exposition-only

    template<
            class I1,
            class I2,
            class Comp,
            class Proj1,
            class Proj2
    >
    concept three_way_invocable =
        input_iterator<I1> &&
        input_iterator<I2> &&
        std::regular_invocable<
            Comp&,
            indirect_result_t<Proj1, I1>,
            indirect_result_t<Proj2, I2>> &&
            is_three_way_ordering<I1, I2, Comp, Proj1, Proj2>; //exposition-only


    template<
            class I1,
            class I2,
            class Comp,
            class Proj1,
            class Proj2
    >
    concept three_way_comperator =
        std::indirectly_readable<I1> &&
        std::indirectly_readable<I2> &&
        std::copy_constructible<Comp> &&
        three_way_invocable<I1, I2, Comp&, Proj1&, Proj2&>;


    template<
        input_iterator I1, sentinel_for<I1> S1,
        input_iterator I2, sentinel_for<I2> S2,
        class Comp = compare_three_way,
        class Proj1 = identity, 
        class Proj2 = identity
    >
    requires
        three_way_comperator<I1, I2, Comp, Proj1, Proj2>
    constexpr auto
        lexicographical_compare_three_way( 
            I1 first1, 
            S1 last1, 
            I2 first2, 
            S2 last2, 
            Comp comp = {},
            Proj1 proj1 = {}, 
            Proj2 proj2 = {}
    ) -> three_way_comparator_result_t<I1, I2, Comp, Proj1, Proj2>
    {
        while (first1 != last1)
        {
            if (first2 == last2)
            {
                return strong_ordering::greater;
            }

            if (auto cmp = comp(proj1(*first1), proj2(*first2)); 
                cmp != 0 ) 
            {
                return cmp;
            }

            ++first1;
            ++first2;
        }

        // GCC 11 implementation with the
        // note: See PR 94006
        return (first2 == last2) <=> true; 
    } 

    template<
        ranges::input_range R1,
        ranges::input_range R2,
        class Comp = compare_three_way,
        class Proj1 = identity, 
        class Proj2 = identity
    >
    requires
    three_way_comperator<iterator_t<R1>, iterator_t<R2>, Comp, Proj1, Proj2>
    constexpr auto
        lexicographical_compare_three_way( 
            R1&& r1,
            R2&& r2,
            Comp comp = {},
            Proj1 proj1 = {}, 
            Proj2 proj2 = {}
    ) -> three_way_comparator_result_t<iterator_t<R1>, iterator_t<R2>, Comp, Proj1, Proj2>
     {
         return lexicographical_compare_three_way(
                 ranges::begin(r1), ranges::end(r1),
                 ranges::begin(r2), ranges::end(r2),
                 move(comp),
                 move(proj1),
                 move(proj2));
     }
}

