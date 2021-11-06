#include <functional>
#include <type_traits>
#include <tuple>
#include <new>
#include <optional>
#include <exception>

extern "C" int printf(char const*, ...) noexcept;
extern "C" int puts(char const*) noexcept;

//using std::invoke_result_t;

// C++20 concepts
template<class T, class... As>
concept constructible_from = std::is_constructible_v<T, As...>;

template<class T>
concept move_constructible = constructible_from<T, T>;

template<class T>
concept copy_constructible =
    move_constructible<T> &&
    constructible_from<T, T const&>;

template<class A, class B>
concept derived_from = std::is_base_of_v<B, A>;

template<class F, class... As>
concept invocable = requires {
    typename std::invoke_result_t<F, As...>;
};

template<class R, class... As>
    requires requires(R&& r, As&&... as) {
        ((R&&)r).set_value((As&&) as...);
    }
void set_value(R&& r, As&&... as)
    noexcept(noexcept(((R&&)r).set_value((As&&) as...))) {
    ((R&&)r).set_value((As&&) as...);
}

template<class R, class E>
    requires requires(R&& r, E&& e) {
        {((R&&)r).set_error((E&&) e)} noexcept;
    }
void set_error(R&& r, E&& e) noexcept {
    ((R&&)r).set_error((E&&) e);
}


template<class R>
    requires requires(R&& r) {
        {((R&&)r).set_done()} noexcept;
    }
void set_done(R&& r) noexcept {
    ((R&&)r).set_done();
}

template<class R, class E = std::exception_ptr>
concept receiver =
    move_constructible<std::remove_cvref_t<R>> &&
    requires (R&& r, E&& e) {
        ::set_error((R&&) r, (E&&) e);
        ::set_done((R&&) r);
    };

template<class R,  class... As>
concept receiver_of =
    receiver<R> &&
    requires (R&& r, As&&... as) {
        ::set_value((R&&) r, (As&&) as...);
    };

template<class R, class... As>
inline constexpr bool is_nothrow_receiver_of_v =
    noexcept(::set_value(std::declval<R>(), std::declval<As>()...));

struct sender_base {};

template<class S>
struct sender_traits;

template<class S>
  requires derived_from<S, sender_base>
struct sender_traits<S> {};

template<class S>
concept sender =
    move_constructible<std::remove_cvref_t<S>> &&
    requires {
        // Opt-in to sender-ness by specializing sender_traits
        sizeof(sender_traits<std::remove_cvref_t<S>>);
    };

static_assert(!sender<int>);


// start function
template<class O>
requires requires(O&& o) {
    {((O&&)o).start()} noexcept;
} 
void start(O&& o) noexcept {
    ((O&&)o).start();
}

// operation_state
template<class O>
concept operation_state =
    std::is_object_v<O> &&
    requires (O&& o) {
        start((O&&)o);
    };

// connect function
template<sender S, receiver R>
    requires requires(S&& s, R&& r) {
        {((S&&)s).connect((R&&) r)} -> operation_state;
    } 
auto connect(S&& s, R&& r) noexcept(noexcept(((S&&)s).connect((R&&)r))) 
{
    return ((S&&)s).connect((R&&)r);
}


template<class S, class R>
concept sender_to =
    sender<S> &&
    receiver<R> &&
    requires(S&& s, R&& r) {
        ::connect((S&&)s, (R&&)r);
    };

template<class S, class R>
    requires sender_to<S, R>
using state_t =
    decltype(::connect(std::declval<S>(), std::declval<R>()));

#include "then.h"


// A useful immediately executing multi-shot sender that sends some
// values through the value channel.
template<move_constructible... Ts>
struct just : sender_base {
    std::tuple<Ts...> ts_;
    explicit(sizeof...(Ts) == 1) constexpr just(Ts... ts):
        ts_{(Ts&&) ts...} {}

    template<receiver_of<Ts...> R>
    struct _op {
        R r_;
        std::tuple<Ts...> ts_;
        void start() && noexcept
        { 
            try {   
                std::apply([this](Ts&&...ts) mutable {
                    ::set_value((R&&)r_, (Ts&&)ts...);
                }, (std::tuple<Ts...>&&)ts_);
            } catch(...) {
                ::set_error((R&&) r_, std::current_exception());
            }
        }
    };
    template<receiver_of<Ts...> R>
        requires (copy_constructible<Ts> &&...)
    auto connect(R r) const & -> _op<R> {
        return _op<R>{(R&&)r, ts_};
    }
    template<receiver_of<Ts...> R>
    auto connect(R r) && -> _op<R> {
        return _op<R>{(R&&)r, (std::tuple<Ts...>&&)ts_};
    }
};


// default sink object
inline constexpr struct _sink {
    void set_value(auto&&...) const noexcept {}
    [[noreturn]] void set_error(auto&&) const noexcept {
        std::terminate();
    }
    [[noreturn]] void set_done() const noexcept {
        std::terminate();
    }
} sink;


int main() {
    auto j = just(1,2,3);
    auto f = [](int i, int j, int k) noexcept {
        printf("i=%d, j=%d, k=%d\n", i, j, k);
    };

    auto s1 = then(j,f);
    auto connection = connect(std::move(s1),std::move(sink));
    ::start(std::move(connection));
}

