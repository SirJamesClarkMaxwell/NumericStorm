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
   using Operations = typename SettingsT::operation_l::operations_e;

    BasicSimplexStrategy(const SettingsT& settings)
        : VisitorOperationBase<SettingsT>{settings} {}

    virtual ~BasicSimplexStrategy() = default;


    typename SettingsT::Out operator()(typename SettingsT::In& state)
    {
        switch (state.getCurrentOperation())
        {
        case Operations::Reflection:
            if (reflectionDecision(state)) {
                state.getWorstPoint() = state[Reflected];

                return reset(state);
            }

            if (expansionCondition(state))
                state.getCurrentOperation() = Operations::Expansion;
            else
                state.getCurrentOperation() = Operations::Contraction;

            return true;
            break;
        case OperationE::Expansion:
            if (expansionDecision(state))
                state.getWorstPopint() = state[Expanded];
            else
                state.getWorstPoint() = state[Reflected];

            return reset(state);
            break;
        case OperationE::Contraction:
            if (contractionDecision(state)) {
                state.getWorstPoint() = state[Contracted];

                return reset(state);
            }

            state.getCurrentOperation() = Operations::Shrinking;
            return true;
            break;
        case OperationE::Srinking:

            return reset();
            break;
        default:
            break;
        }
    }

    bool reset(typename SettingsT::In& state) { state.getCurrentOperation = OperationE::Reflection; return false; }
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