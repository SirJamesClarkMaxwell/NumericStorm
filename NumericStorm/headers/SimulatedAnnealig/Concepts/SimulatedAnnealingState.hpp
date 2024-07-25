#pragma once
#include <vector>
#include <concepts>

namespace NumericStorm::Concepts {
    template <typename T>
    concept SimulatedAnnealingState = requires(T t, const T ct, const std::vector<double>&vec) {
        
        { t.getEnergies() } -> std::same_as<std::vector<double*>&>;
        { t.getConfigurations() } -> std::same_as<std::vector<std::vector<double*>>&>;
    
        { ct.getEnergies() } -> std::same_as<const std::vector<double*>&>;
        { ct.getConfigurations() } -> std::same_as<const std::vector<std::vector<double*>>&>;
        { ct.getEnergy(vec) } -> std::same_as<double>;

        { ct.getAnnealedEnergies() } -> std::same_as<std::vector<double>&>;
        { ct.getAnnealedConfigurations() } -> std::same_as<std::vector<std::vector<double>>&>;
        { ct.getTemperature() } -> std::same_as<double&>;
        { ct.getBackOffset() } -> std::same_as<size_t&>;
    };
};