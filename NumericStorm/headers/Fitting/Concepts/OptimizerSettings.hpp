#pragma once

#include "OptimizerStateWrapper.hpp"

namespace NumericStorm::Concepts {
    template <typename St>
    concept OptimizerSettings = requires {
        typename St::OptimizerInputT;
        typename St::OptimizerStateT;
        typename St::OptimizerOutputT;
        typename St::AuxilaryParametersT;
        { St::parameter_size } -> std::same_as<const size_t>;
    
        requires OptimizerStateWrapper<typename St::OptimizerStateT>;
        requires OptimizerStateWrapper<typename St::OptimizerOutputT>;
    };
}