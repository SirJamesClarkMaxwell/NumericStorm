#pragma once
#include <vector>
#include <concepts>

namespace NumericStorm::Concepts {
    template <typename T>
    concept SimulatedAnnealingState = requires(T t, const T ct, const std::vector<double>&vec) {
        
        { t.getEnergies() } -> std::convertible_to<std::vector<double*>&>;
        { t.getConfigurations() } -> std::convertible_to<std::vector<std::vector<double*>>&>;
    
        { ct.getEnergies() } -> std::convertible_to<const std::vector<double*>&>;
        { ct.getConfigurations() } -> std::convertible_to<const std::vector<std::vector<double*>>&>;
        { ct.getEnergy(vec) } -> std::convertible_to<double>;

        { ct.getAnnealedEnergies() } -> std::convertible_to<std::vector<double>>;
        { ct.getAnnealedConfigurations() } -> std::convertible_to<std::vector<std::vector<double>>>;
        { ct.getTemperature() } -> std::convertible_to<double>;

        { ct.getAnnealedEnergies() } -> std::convertible_to<const std::vector<double>>;
        { ct.getAnnealedConfigurations() } -> std::convertible_to<const std::vector<std::vector<double>>>;
        { ct.getTemperature() } -> std::convertible_to<const double>;

        { ct.getBackOffset() } -> std::convertible_to<size_t>;
        { ct.getBackOffset() } -> std::convertible_to<const size_t>;
    };
};