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
template <size_t parameter_size>
class BasicSimplexDecision : public IDecision<parameter_size>
{

public:
    BasicSimplexDecision() = default;
    BasicSimplexDecision(const BasicSimplexDecision<parameter_size>&) = default;
    BasicSimplexDecision(BasicSimplexDecision<parameter_size>&&) = default;
    BasicSimplexDecision<parameter_size>& operator=(const BasicSimplexDecision<parameter_size>&) = default;
    BasicSimplexDecision<parameter_size>& operator=(BasicSimplexDecision<parameter_size>&&) = default;


    virtual ~BasicSimplexDecision() = default;
    virtual bool operator()(SimplexIntermediatePoints<parameter_size>& simplexIntPoints) override
    {
        //todo add ternary operator
        //todo add alias for the simplexIntPoints.simplexFigure
        switch (m_curr_operation)
        {
        case "reflection":
            if (reflectionDecision(simplexIntPoints)) {
                simplexIntPoints.m_simplexFigure[secondWorstPoint] = simplexIntPoints[Reflected];
                return reset();
                //NOTE 5b. we need to check that in both cases expansion and reflection of returned reflection type
            }

            if (expansionCondition(simplexIntPoints))
                m_curr_operation = "expansion";
            else
                m_curr_operation = "contraction";
            return true;
            break;
        case "expansion":
            if (expansionDecision(simplexIntPoints))
                simplexIntPoints.m_simplexFigure[worstPoint] = simplexIntPoints[Expanded];
            else
                simplexIntPoints.m_simplexFigure[worstPoint] = simplexIntPoints[Reflected];
            return reset();
            break;
        case "contraction":
            if (contractionDecision(simplexIntPoints)) {
                simplexIntPoints.m_simplexFigure[secondWorstPoint] = simplexIntPoints.[Contracted];
                return false;
            }
            m_curr_operation = "shrinking";
            return true;
            break;
        case "shrinking":
            return reset();
            break;
        default:
            break;
        }
    }
    const std::string& getOperation() const { return m_curr_operation; }
    bool reset() { m_curr_operation = "reflection"; return false; }
private:

    const bool contractionDecision(const SimplexIntermediatePoints<parameter_size>& simplexIntPoints)
    {
        return simplexIntPoints.m_simplexFigure[Contracted] <= simplexIntPoints[Reflected];
    }
    const bool expansionDecision(const SimplexIntermediatePoints<parameter_size>& simplexIntPoints)
    {
        return simplexIntPoints.m_simplexFigure[Expanded] < simplexIntPoints[Reflected];
    }
    const bool expansionCondition(const SimplexIntermediatePoints<parameter_size>& simplexIntPoints)
    {
        return simplexIntPoints[Reflected] < simplexIntPoints.m_simplexFigure[bestPoint];
    }
    const bool reflectionDecision(const SimplexIntermediatePoints<parameter_size>& simplexIntPoints)
    {
        return simplexIntPoints.m_simplexFigure[bestPoint] <= simplexIntPoints[Reflected] && simplexIntPoints[Reflected] < simplexIntPoints.m_simplexFigure[secondWorstPoint];
    }
    std::string m_curr_operation{ "reflection" };

};
}