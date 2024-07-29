#pragma once
#include <string>

#include "VisitorOperationBase.hpp"
#include "SimplexStrategySettings.hpp"
#include "OperationSettings.hpp"



namespace NumericStorm::Fitting
{
using namespace NumericStorm::Concepts;

template<size_t parameter_size>
class BasicSimplexStrategy : public VisitorOperationBase<SimplexStrategySettings<parameter_size>>
{

public:
    using SettingsT = typename VisitorOperationBase<SimplexStrategySettings<parameter_size>>::SettingsT;
   using Operations = typename SettingsT::operation_l::operations_e;
   
   BasicSimplexStrategy() = default;

    BasicSimplexStrategy(const SettingsT& settings)
        : VisitorOperationBase<SettingsT>{settings} {}

    virtual ~BasicSimplexStrategy() = default;


    typename SettingsT::Out operator()(typename SettingsT::In& state)
    {
        switch (state.getCurrentOperation())
        {
        case Operations::Reflect:
            if (reflectionDecision(state)) {
                state.getWorstPoint() = state[Reflected];

                return reset(state);
            }

            if (expansionCondition(state))
                state.getCurrentOperation() = Operations::Expand;
            else
                state.getCurrentOperation() = Operations::Contract;

            return true;
            break;
        case Operations::Expand:
            if (expansionDecision(state))
                state.getWorstPoint() = state[Expanded];
            else
                state.getWorstPoint() = state[Reflected];

            return reset(state);
            break;
        case Operations::Contract:
            if (contractionDecision(state)) {
                state.getWorstPoint() = state[Contracted];

                return reset(state);
            }

            state.getCurrentOperation() = Operations::Shrink;
            return true;
            break;
        case Operations::Shrink:

            return reset(state);
            break;
        default:
            break;
        }
    }

    bool reset(typename SettingsT::In& state) { state.getCurrentOperation() = Operations::Reflect; return false; }
private:

    bool contractionDecision(const typename SettingsT::In& state) const
    {
        return state[Contracted] <= state[Reflected];
    }
    bool expansionDecision(const typename SettingsT::In& state) const
    {
        return state[Expanded] < state[Reflected];
    }
    bool expansionCondition(const typename SettingsT::In& state) const
    {
        return state[Reflected] < state.getWorstPoint();
    }
    bool reflectionDecision(const typename SettingsT::In& state) const
    {
        return state.getBestPoint() <= state[Reflected] && state[Reflected] < state.getSecondWorstPoint();
    }

};
}