#pragma once

#include "OperationBase.hpp"

namespace NumericStorm::Concepts {
    template <typename T>
    concept Operation = OperationBase<T> && requires(T t, typename T::SettingsT::In input, typename const T::SettingsT& settings) {
        { t(input) } -> std::same_as<typename T::SettingsT::Out>;
        { T(settings) };
    };
}