#pragma once

#include "OperationBase.hpp"

namespace NumericStorm::Concepts {
    template <typename T>
    concept Operation = OperationBase<T> && requires(T t, T::SettingsT::In input, const T::SettingsT& settings) {
        { t(input) } -> std::same_as<typename T::SettingsT::Out>;
        { T(settings) };
    };
}