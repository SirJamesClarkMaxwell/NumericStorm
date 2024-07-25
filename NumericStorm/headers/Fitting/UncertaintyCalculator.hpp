#pragma once

#include <concepts>
#include <vector>
#include <array>

#include "Data.hpp"
#include "Optimizer.hpp"
#include "UncertaintyStrategyWrapper.hpp"

namespace NumericStorm::Fitting
{
    using namespace NumericStorm::Concepts;

    
    
    template<Optimizer O, UncertaintyStrategyWrapper<O> Wrapper>
    class UncertaintyCalculator
    {
    public:
        UncertaintyCalculator(const Wrapper& wrapper)
            : m_wrapper{ wrapper } {}
    
        void updateWrapper(const Wrapper& wrapper) { m_wrapper = wrapper; }
        Wrapper& getWrapper() { return m_wrapper; }
        const Wrapper& getWrapper() const { return m_wrapper; }
        
        std::vector<std::vector<double>> operator()(const O& optimizer, const typename O::SettingsT::OptimizerInputT& input, const Data& data, const typename O::SettingsT::AuxParameters& addPar) { 
            return m_wrapper.calculateUncertainty(optimizer, input, data, addPar); 
        }
    private:
        Wrapper m_wrapper{};
    };

}