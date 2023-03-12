#include <concepts> 

template <typename T, typename... U>
concept same_as_any_of = (std::same_as<T, U> || ...);

template <typename T, typename... U>
concept converible_to_any_of = (std::convertible_to<T, U> || ...);

namespace impl{
    template <typename T, typename... U> 
    struct convertible_counter{
        constexpr static std::size_t counter_ = (static_cast<int>(std::convertible_to<T, U>) + ...);
    };
}

template <typename T, typename... U>
concept converible_to_one_of = impl::convertible_counter<T, U...>::counter_ == 1;

template <typename T, typename... U>
concept converible_to_all_of = impl::convertible_counter<T, U...>::counter_ == sizeof...(U);

