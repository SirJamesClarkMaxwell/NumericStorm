#pragma once

#include <concepts>
#include <type_traits>

#include "OptimizerStateWrapper.hpp"

namespace NumericStorm::Concepts
{
    template <typename A, typename In, typename Out>
    concept Adapter = requires(In in) {
        requires OptimizerStateWrapper<In>;
        requires OptimizerStateWrapper<Out>;
        { A::adapt(in) } -> std::same_as<Out>;
    };
};