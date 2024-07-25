#pragma once

#include <concepts>
#include <vector>

#include "Optimizer.hpp"
#include "Data.hpp"

namespace NumericStorm::Concepts {

using namespace NumericStorm::Fitting;

    template<typename W, typename O>
    concept UncertaintyStrategyWrapper = requires (W strategy, const O & optimizer, const Data & data, const typename O::SettingsT::OptimizerInputT & input, const typename O::SettingsT::AuxParameters & addPar)
    {
        requires Optimizer<O>;
        { strategy.calculateUncertainty(optimizer, input, data, addPar) } -> std::convertible_to<std::vector<std::vector<double>>>;
    };
};