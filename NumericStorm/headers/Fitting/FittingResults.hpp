#pragma once
#include <array>
#include <concepts>
#include <vector>

namespace NumericStorm::Fitting {
template<class Input>
concept FittingInput = requires(Input input)
{
    { input.getNumbers() } -> std::convertible_to<std::vector<double>>;
    //TODO: change the name of this method to be more accurate
    { input.getError() } ->std::convertible_to<double>;
};
template<class Input>
    requires FittingInput<Input>
struct FittingResults
{
public:
    FittingResults(const Input fittingResults, int iterationCounts, std::vector<std::vector<double>> covarianceMatrix)
        :
        fittingResults{ fittingResults },
        iterationCounts{ iterationCounts },
        minimum_error{ fittingResults.getError() },
        covarianceMatrix{ covarianceMatrix } {};
    Input fittingResults{};
    int iterationCounts{ 0 };
    double minimum_error{ -1 };
    std::vector<std::vector<double>> covarianceMatrix{};

};
}