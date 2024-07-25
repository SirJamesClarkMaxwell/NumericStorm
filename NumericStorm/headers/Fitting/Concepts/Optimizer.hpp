#pragma once

#include <type_traits>
#include <concepts>

#include "OptimizerSettings.hpp"

namespace NumericStorm::Concepts {
    template<typename O>
    concept Optimizer = requires(O o, const typename O::SettingsT::OptimizerInputT & input, const typename O::Data & data, const typename O::SettingsT::AuxilaryParametersT & auxParams, typename O::SettingsT::OptimizerStateT & state) {
        typename O::SettingsT;
        typename O::AdapterT;
    
        requires OptimizerSettings<typename O::SettingsT>;
    
        { o.setUpOptimization(input, data, auxParams) } -> std::same_as<typename O::SettingsT::OptimizerStateT>;
        { o.checkStop(state) } -> std::same_as<bool>;
        { o.oneStep(state) } -> std::same_as<void>;
        { o.getResults(state) } -> std::same_as<const typename O::SettingsT::OptimizerOutputT&>;
        { o.setUp() } -> std::same_as<void>;
    };
}