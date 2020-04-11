
// include local array implementation with the
// added c_array() functionality
#include "array"

// setup for the examples
constexpr int ARRAY_SIZE = 8;
using element_t = int;

// declaring types to verify
// the correct function call
struct ref {};
struct const_ref {};
struct pointer {};
struct const_pointer {};
struct rvalue_ref {};
struct const_rvalue_ref {};

// overloads to verify correct
// overload resolution

ref foo(element_t (&ar)[ARRAY_SIZE]) {
	return {};
}

const_ref foo(const element_t (&ar)[ARRAY_SIZE]) {
	return {};
}

pointer foo(element_t (*ar)[ARRAY_SIZE]) {
	return {};
}

const_pointer foo(const element_t (*ar)[ARRAY_SIZE]) {
	return {};
}

rvalue_ref foo(element_t(&&ar)[ARRAY_SIZE]) {
	return {};
}

const_rvalue_ref foo(const element_t(&&ar)[ARRAY_SIZE]) {
	return {};
}

// assert-is-same-type assistance function
template <typename ExpectedType, typename ActualType>
void assert_is_same(ActualType&&) {
	static_assert(std::is_same<ExpectedType, ActualType>::value, "types are not the same");
}

int main() {

	// use a simple array in all tests
	using array_t = std::array<element_t, ARRAY_SIZE>;
	{
		// mutable ref and pointer
		array_t arr{};
		assert_is_same<ref>(foo(arr.c_array()));
		assert_is_same<pointer>(foo(&arr.c_array()));
	}
	{
		// const ref and pointer
		const array_t arr{};
		assert_is_same<const_ref>(foo(arr.c_array()));
		assert_is_same<const_pointer>(foo(&arr.c_array()));
	}
	{
		// function returning rvalue array_t
		auto get_arr = []() -> array_t { return {}; };
		assert_is_same<rvalue_ref>(foo(get_arr().c_array()));
	}
	{
		// function returning const rvalue array_t
		auto get_arr = []() -> const array_t { return {}; };
		assert_is_same<const_rvalue_ref>(foo(get_arr().c_array()));
	}

	return 0;
}
