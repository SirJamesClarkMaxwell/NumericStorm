#pragma once
#include <array>


namespace NumericStorm::Fitting {
template<size_t parameters_size>
struct FittingResults
{
public:
    FittingResults(const Parameters<parameters_size> parameters, int iterationCounts, double minimalError)
        :m_parameters{ parameters }, m_iterationCounts{ iterationCounts }, m_minimum_error{ minimalError } {}
    Parameters<parameters_size> m_parameters{};
    int m_iterationCounts{ 0 };
    double m_minimum_error{ -1 };
    std::array<std::array<double, parameters_size>, parameters_size> m_covariance_matrix{};

};
}