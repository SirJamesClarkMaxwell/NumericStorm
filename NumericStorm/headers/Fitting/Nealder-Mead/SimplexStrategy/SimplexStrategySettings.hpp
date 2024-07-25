#pragma once

#include "BasicOperationsList.hpp"
#include "BasicSimplexIndeciesEnum.hpp"


namespace NumericStorm::Fitting {

    template<size_t parameter_size>
    class SimplexStrategySettings {
    public:
        using operation_l = BasicOperationsList<parameter_size>;
        using indecies = BasicSimplexIndeciesEnum;
        using In = SimplexIntermediateState<parameter_size, indecies, typename operation_l::operations_e>;
        using Out = bool;
    };
}