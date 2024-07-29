#pragma once

#include <type_traits>
#include <concepts>

namespace NumericStorm::Concepts {
    template<typename T = void>
    concept OptimizerStateWrapper = std::is_void_v<T> || requires(T t) {
        typename T::WrappedStateT;
        
        { t.getWrappedState() } -> std::convertible_to<typename T::WrappedStateT>;
        { t.getWrappedState() } -> std::convertible_to<const typename T::WrappedStateT>;

    };
}