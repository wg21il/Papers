
#include "array"
#include <type_traits>

constexpr int array_size = 8;
using element_t = int;

struct ref{};

ref foo( element_t (&ar)[array_size] ){
    return {};
}

struct const_ref{};

const_ref foo( const element_t (&ar)[array_size] ){
    return {};
}

struct pointer {};

pointer foo( element_t (*ar)[array_size] ){
    return {};
}

struct const_pointer{};

const_pointer foo( const element_t (*ar)[array_size] ){
    return {};
}

struct rvalue_ref{};

rvalue_ref foo( element_t (&&ar)[array_size] ){
    return {};
}

template<typename Expected, typename Actual>
void assert_type_is(Actual &&) {
    static_assert(std::is_same_v<Expected, Actual>, "Types are not the same");
}

int main()
{
    using array_t = std::array<element_t, array_size>;
    {
        array_t arr = {0};
        assert_type_is<ref>(foo(arr.c_array()));
        assert_type_is<pointer>(foo(&arr.c_array()));
    }
    {
        const array_t arr = {0};
        assert_type_is<const_ref>(foo(arr.c_array()));
        assert_type_is<const_pointer>(foo(&arr.c_array()));
    }
    {
        auto get_arr = []()->array_t{
            return {0};
        };
        assert_type_is<rvalue_ref>(foo(get_arr().c_array()));
    }
    {
        auto get_arr = []()->const array_t{
            return {0};
        };
        assert_type_is<const_ref>(foo(get_arr().c_array()));
    }

    return 0;
}
