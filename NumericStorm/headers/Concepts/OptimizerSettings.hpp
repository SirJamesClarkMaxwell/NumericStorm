#pragma once

#include "OptimizerStateWrapper.hpp"

namespace NumericStorm::Concepts {
    template <typename St>
    concept OptimizerSettings = requires {
        typename St::OptimizerInputT;
        typename St::OptimizerStateT;
        typename St::OptimizerOutputT;
        typename St::AuxilaryParametersT;
        typename St::parameter_size;
    
        requires OptimizerStateWrapper<typename St::OptimizerStateT>;
        requires OptimizerStateWrapper<typename St::OptimizerOutputT>;
    };
}