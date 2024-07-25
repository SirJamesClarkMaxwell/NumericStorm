#pragma once
#include <vector>

#include "Optimizer.hpp"
#include "MonteCarloSettings.hpp"
#include "Data.hpp"


namespace NumericStorm::MonteCarlo
{
using namespace NumericStorm::Concepts;

template<class E, class O>
concept Executor = requires(E executor,
    const O & optimizer,
    const typename typename O::SettingsT::OptimizerInputT & input,
    const Data & data,
    const typename O::SettingsT::AuxParameters & addPar,
    size_t size,
    ExecutionPolicy policy)
{
    requires Optimizer<O>;
    { executor(optimizer, input, data, addPar) } -> std::same_as<std::vector<typename O::SettingsT::OptimizerOutputT>>;
    { executor.setBatchSize(size) } -> std::same_as<void>;
    { executor.setPolicy(policy) } -> std::same_as<void>;
	{ executor.getBatchSize() } -> std::same_as<size_t>;
	{ executor.getPolicy() } -> std::same_as<ExecutionPolicy>;
};





template<Optimizer O, Executor<O> E>
class MonteCarlo
{
public:

    MonteCarlo(const MonteCarloSettings& settings) : m_settings{ settings } {}
   
    std::vector<typename O::SettingsT::OptimizerOutputT> runSimulations(const O& optimizer, const typename O::SettingsT::OptimizerInputT& input, const Data& data, const typename O::SettingsT::AuxParameters& addPar)
    {
        m_executor.setBatchSize(m_settings.m_batchSize);
        m_executor.setPolicy(m_settings.m_executionPolicy);
        return m_executor(optimizer, input, data, addPar);
    };

    ~MonteCarlo() = default;
private:
    E m_executor{};
    MonteCarloSettings m_settings{};
};

}