#pragma once
#include "./../BasicSimplex/BasicSimplexOptimizer.hpp"
#include "./../../SimulatedAnnealig/SimulatedAnnealingFactory.hpp"

namespace NumericStorm::Fitting
{
template<class Optimizer, class InitialParameters, size_t parameter_size, class SetUpOutput>
class SimulatedAnnealingSimplexOptimizer
{
public:
    SimulatedAnnealingSimplexOptimizer(Optimizer& optimizer)
        :m_optimizer{ optimizer } {};
public:
    SetUpOutput setUpFittingProcedure(InitialParameters& initialParameters, Data& fittingData, AdditionalParameters additionalParameters);
    void oneStepAlgorithm(SetUpOutput output);
    void calculateUncertainty();
    bool checkStopCondition() { return m_optimizer.checkStopCondition(); }
    FittingResults<parameter_size> getResult(return m_result);
private:
    using namespace SimulatedAnnealing;
    Optimizer m_optimizer;
    FittingResults<parameter_size> m_result{};
    SimulatedAnnealingFactory m_simulatedAnnealingFactory;

};
template<class Optimizer, class InitialParameters, size_t parameter_size, class SetUpOutput>
using classType = SimulatedAnnealingSimplexOptimizer<Optimizer, InitialParameters, parameter_size, SetUpOutput>

template<class Optimizer, class InitialParameters, size_t parameter_size, class SetUpOutput>
SetUpOutput classType::setUpFittingProcedure(InitialParameters& initialParameters, Data& fittingData, AdditionalParameters additionalParameters)
{

};

template<class Optimizer, class InitialParameters, size_t parameter_size, class SetUpOutput>
void SimulatedAnnealingSimplexOptimizer<Optimizer, InitialParameters, parameter_size, SetUpOutput>::oneStepAlgorithm(SetUpOutput output)
{
    // Output output = m_optimizer.oneStepAlgoritm(output);
    // Result result = m_simulatedAnnealingFactory.anneal(output);
    // return result;
};
template<class Optimizer, class InitialParameters, size_t parameter_size, class SetUpOutput>
void SimulatedAnnealingSimplexOptimizer<Optimizer, InitialParameters, parameter_size, SetUpOutput>::calculateUncertainty()
{
};


}
