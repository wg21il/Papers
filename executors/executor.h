
#include <concepts>
#include <functional>

namespace execution{

template<class E, class F>
void execute(E&&, F&&);

template<class E, class F>
concept executor_of_impl =
    std::invocable<std::remove_cvref_t<F>&>               &&
    std::constructible_from<std::remove_cvref_t<F>, F>    &&
    std::move_constructible<std::remove_cvref_t<F>>       &&
    std::copy_constructible<E>                       &&
    std::is_nothrow_copy_constructible_v<E>          &&
    std::equality_comparable<E>                      &&
    requires(const E& e, F&& f) {
        execution::execute(e, (F&&)f);
    };

// implementation specific
using invocable_archetype = std::function<void()>;

template<class E>
concept executor =
    executor_of_impl<E, execution::invocable_archetype>;

template<class E, class F>
concept executor_of =
    executor<E> &&
    executor_of_impl<E, F>;

}

