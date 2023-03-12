

#include "catch2/catch_all.hpp"

TEST_CASE("basic_check")
{
    static_assert(same_as_any_of<int, double, long, int>);
    static_assert(converible_to_any_of<int, double, long>);
    static_assert(converible_to_one_of<int, char*, long>);
    static_assert(converible_to_all_of<int, double, long long, long>);
}
