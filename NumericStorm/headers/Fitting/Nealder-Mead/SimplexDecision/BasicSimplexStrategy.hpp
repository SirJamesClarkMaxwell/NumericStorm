#pragma once
#include <string>

#include "IDecision.hpp"
#include "SimplexFigure.hpp"
#include "SimplexIntermediatePoints.hpp"



//todo 1. add simplexOperationFactory
//todo 2. copy my functions to checking conditions
//todo 3. check validity of these functions
//todo 4. remove the existing conditions by mine
//todo 5a. add recursive invoking of calling operator 

//todo 6. remove ugly {} where we could do it
namespace NumericStorm::Fitting
{
enum Stage {
    SReflection,
    SExpansion,
    SContraction,
    SShrinking
};

template <size_t parameter_size>
class BasicSimplexDecision : public IDecision<parameter_size>
{

public:
    BasicSimplexDecision() = default;
    BasicSimplexDecision(const BasicSimplexDecision<parameter_size>&) = default;
    BasicSimplexDecision(BasicSimplexDecision<parameter_size>&&) = default;
    BasicSimplexDecision<parameter_size>& operator=(const BasicSimplexDecision<parameter_size>&) = default;
    BasicSimplexDecision<parameter_size>& operator=(BasicSimplexDecision<parameter_size>&&) = default;

    BasicSimplexDecision(const StrategySettings& settings) : IDecision<parameter_size>{ settings } {}
    using enum Stage;

    virtual ~BasicSimplexDecision() = default;
    virtual bool operator()(SimplexIntermediatePoints<parameter_size>& simplexIntPoints) override
    {
        //todo add ternary operator
        //todo add alias for the simplexIntPoints.simplexFigure
        //!!! switch supports only int and int like stuff that is comparable during compilation
        //! will switch to enum
        switch (m_curr_operation)
        {
        case SReflection:
            if (reflectionDecision(simplexIntPoints)) {
                simplexIntPoints.m_simplexFigure[worstPoint] = simplexIntPoints[Reflected];
                simplexIntPoints.m_currentOperation = "reflection";

                return reset();
                //NOTE 5b. we need to check that in both cases expansion and reflection of returned reflection type
            }

            if (expansionCondition(simplexIntPoints))
                m_curr_operation = SExpansion;
            else
                m_curr_operation = SContraction;

            simplexIntPoints.m_currentOperation = m_curr_operation == SExpansion ? "expansion" : "contraction";
            return true;
            break;
        case SExpansion:
            if (expansionDecision(simplexIntPoints))
                simplexIntPoints.m_simplexFigure[worstPoint] = simplexIntPoints[Expanded];
            else
                simplexIntPoints.m_simplexFigure[worstPoint] = simplexIntPoints[Reflected];

            simplexIntPoints.m_currentOperation = "reflection";
            return reset();
            break;
        case SContraction:
            if (contractionDecision(simplexIntPoints)) {
                simplexIntPoints.m_simplexFigure[worstPoint] = simplexIntPoints[Contracted];
                simplexIntPoints.m_currentOperation = "reflection";

                return reset();
            }

            m_curr_operation = SShrinking;
            simplexIntPoints.m_currentOperation = "shrinking";
            return true;
            break;
        case SShrinking:

            simplexIntPoints.m_currentOperation = "reflection";
            return reset();
            break;
        default:
            break;
        }
    }
    Stage getOperation() const { return m_curr_operation; }
    bool reset() { m_curr_operation = SReflection; return false; }
private:

    bool contractionDecision(const SimplexIntermediatePoints<parameter_size>& simplexIntPoints) const
    {
        return simplexIntPoints[Contracted] <= simplexIntPoints[Reflected];
    }
    bool expansionDecision(const SimplexIntermediatePoints<parameter_size>& simplexIntPoints) const
    {
        return simplexIntPoints[Expanded] < simplexIntPoints[Reflected];
    }
    bool expansionCondition(const SimplexIntermediatePoints<parameter_size>& simplexIntPoints) const
    {
        return simplexIntPoints[Reflected] < simplexIntPoints.m_simplexFigure[IDecision<parameter_size>::bestPoint];
    }
    bool reflectionDecision(const SimplexIntermediatePoints<parameter_size>& simplexIntPoints) const
    {
        return simplexIntPoints.m_simplexFigure[IDecision<parameter_size>::bestPoint] <= simplexIntPoints[Reflected] && simplexIntPoints[Reflected] < simplexIntPoints.m_simplexFigure[secondWorstPoint];
    }
    Stage m_curr_operation{ SReflection };

};
}