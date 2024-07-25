#pragma once

namespace NumericStorm::MonteCarlo
{
    enum class ExecutionPolicy
    {
        SingleThread,
        MultiThread
    };
    
    struct MonteCarloSettings
    {
        size_t m_batchSize{ 1 };
        ExecutionPolicy m_executionPolicy = ExecutionPolicy::MultiThread;
    };
}