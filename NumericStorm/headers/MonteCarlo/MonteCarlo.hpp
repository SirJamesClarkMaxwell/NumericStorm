#pragma once
#include <vector>
#include <iostream>
#include <array>
#include <memory>
#include <functional>
#include <execution>


namespace MonteCarlo
{
template<class ExecutorWrapper, class Input>
concept Executor = requires(ExecutorWrapper executorWrapper, Input input, int simulationNumber)
{
    { executorWrapper.setUp(input) } -> std::convertible_to<void>;
    { executorWrapper.execute(simulationNumber) } -> std::convertible_to<void>;
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

template<class ExecutorWrapper, class Input>
    requires Executor<ExecutorWrapper, Input>
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
    void runSimulation()
    {
        std::for_each(m_executionPolicy, m_executor.begin(), m_executor.end()
            [this](int simulationNumber) {m_executor.execute(simulationNumber);})
    };

    ~MonteCarlo() = default;
private:
    ExecutorWrapper m_executor;
    MonteCarloSettings m_settings;
    namespace execution = std::execution;
    execution m_executionPolicy;
};




}