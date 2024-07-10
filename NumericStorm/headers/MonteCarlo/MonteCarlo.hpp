#pragma once
#include <vector>
#include <iostream>
#include <array>
#include <memory>
#include <functional>
#include <execution>


namespace NumericStorm::MonteCarlo
{
template<class ExecutorWrapper, class Input, class AnnealingData>
concept Executor = requires(ExecutorWrapper executorWrapper, Input input, int simulationNumber, AnnealingData & copiedData, const AnnealingData & noisedData)
{
    { executorWrapper.setUp(input) } -> std::convertible_to<void>;
    { executorWrapper.addNoise(copiedData) } ->std::convertible_to<AnnealingData&>;
    { executorWrapper.execute(simulationNumber, noisedData) } -> std::convertible_to<void>;
    { executorWrapper.begin() } -> std::convertible_to<typename ExecutorWrapper::Iterator>;
    { executorWrapper.end() } -> std::convertible_to<typename ExecutorWrapper::Iterator>;
};

enum class ExecutionPolicy
{
    SingleThread,
    MultiThread
};

struct MonteCarloSettings
{

public:
    MonteCarloSettings(size_t numerOfSimulation)
        :numerOfSimulation{ numerOfSimulation } {};
public:
    size_t numerOfSimulation;
    ExecutionPolicy executionPolicy = ExecutionPolicy::MultiThread;

};
//TODO: add noise!
template<class ExecutorWrapper, class Input, class AnnealingData>
    requires Executor<ExecutorWrapper, Input, AnnealingData>
class MonteCarlo
{
public:
    MonteCarlo() = delete;
    explicit MonteCarlo(ExecutorWrapper executor, Input executorInput, MonteCarloSettings settings)
        :m_executor{ executor }, m_settings{ settings }
    {
        m_executor.setUp(executorInput);
        using ExecutionPolicy;
        m_executionPolicy = m_settings.executionPolicy == MultiThread ? execution::par : execution::seq;
    };
    void runSimulation(AnnealingData& dataToNoise)
    {
        std::for_each(m_executionPolicy, m_executor.begin(), m_executor.end(),
            [&](int simulationNumber)
            {
                AnnealingData copiedData(dataToNoise);
                AnnealingData& noisedData = m_executor.addNoise(copiedData);
                m_executor.execute(simulationNumber, noisedData);
                //NOTE all data must be sotred in m_executor by construction -> m_executor must to change his state during the execute method -> results of the MCsim must be received from elsewhere
                    //NOTE  results of the MCsim must be received from elsewhere. Or we will add another struct for this
                //! we need discus the approach to execution, and where data gonna be stored. 
                //NOTE we could create the templated struct where all data gonna be stored and MC class will modify the state of that struct, in realization there will be no difference between 
                    //NOTE m_executor because we need external class which will be modified 
            });
    };

    ~MonteCarlo() = default;
private:
    ExecutorWrapper m_executor;
    MonteCarloSettings m_settings;
    std::execution m_executionPolicy;
};

}