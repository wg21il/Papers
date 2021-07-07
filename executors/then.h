
// "then" algorithm implementation begins here

template<receiver R, class F>
struct _then_receiver {
    R r_;
    F f_;
    _then_receiver(R r, F f) : r_((R&&) r), f_((F&&) f) {}

    template<class... As, class Ret = std::invoke_result_t<F, As...>>
        requires receiver_of<R, Ret> void set_value(As&&... as) &&
        noexcept(std::is_nothrow_invocable_v<F, As...> &&
            is_nothrow_receiver_of_v<R, Ret>) {
        ::set_value((R&&) r_, std::invoke((F&&) f_, (As&&) as...));
    }

    template<class... As, class Ret = std::invoke_result_t<F, As...>>
        requires receiver_of<R> && std::is_void_v<Ret>
    void set_value(As&&... as) &&
        noexcept(std::is_nothrow_invocable_v<F, As...> &&
            is_nothrow_receiver_of_v<R>) {
        std::invoke((F&&) f_, (As&&) as...);
        ::set_value((R&&) r_);
    }
    template<class E>
        requires receiver<R, E>
    void set_error(E&& e) && noexcept {
        ::set_error((R&&) r_, (E&&) e);
    }
    void set_done() && noexcept {
        ::set_done((R&&) r_);
    }
};

template<sender S, class F>
struct _then_sender : sender_base {
    S s_;
    F f_;
    _then_sender(S s, F f) : s_((S&&)s), f_((F&&)f) {}
    template<receiver R>
        requires sender_to<S, _then_receiver<R, F>>
    auto connect(R r) && -> state_t<S, _then_receiver<R, F>> {
        return ::connect((S&&)s_, _then_receiver{(R&&)r, (F&&)f_});
    }
};

template<sender S, class F>
sender auto then(S s, F f) {
    return _then_sender{(S&&)s, (F&&)f};
}

// "then" algorithm implementation ends here

