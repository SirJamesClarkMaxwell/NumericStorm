#pragma once

#include <type_traits>
#include <concepts>

#include "OptimizerSettings.hpp"
#include "Data.hpp"

namespace NumericStorm::Concepts {
using namespace NumericStorm::Fitting;

    template<typename O>
    concept Optimizer = requires(O o, const typename O::SettingsT::OptimizerInputT & input, const Data & data, const typename O::SettingsT::AuxilaryParametersT & auxParams, typename O::SettingsT::OptimizerStateT & state) {
        typename O::SettingsT;
        typename O::AdapterT;
    
        requires OptimizerSettings<typename O::SettingsT>;
    
        { o.setUpOptimization(input, data, auxParams) } -> std::convertible_to<typename O::SettingsT::OptimizerStateT>;
        { o.checkStop(state) } -> std::convertible_to<bool>;
        { o.oneStep(state) } -> std::same_as<void>;
        { o.getResults(state) } -> std::convertible_to<const typename O::SettingsT::OptimizerOutputT>;
        { o.setUp() } -> std::same_as<void>;
    };
}