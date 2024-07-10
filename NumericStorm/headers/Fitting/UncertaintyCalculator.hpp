#pragma once

#include <concepts>
#include <vector>
#include <array>


namespace NumericStorm::Fitting
{

template<class Input>
concept UncertaintyStrategyWrapper = requires (Input input)
{
    { input.calculateUncertainty() } -> std::convertible_to<std::vector<std::vector<double>>>;
};

template<class Input>
    requires UncertaintyStrategyWrapper<Input>
class UncertaintyCalculator
{
public:
    UncertaintyCalculator() = delete;
    UncertaintyCalculator(UncertaintyStrategyWrapper wrapper)
        :m_wrapper{ wrapper } {};
    vector<vector<double>> operator()(Input input) { m_wrapper.calculateUncertainty(); };
private:
    using vector = std::vector;
    UncertaintyStrategyWrapper m_wrapper;
};

}