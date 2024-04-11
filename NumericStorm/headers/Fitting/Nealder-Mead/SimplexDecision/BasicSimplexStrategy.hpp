#include "IDecision.hpp"
#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"
#include <string>

//todo 1. add simplexOperationFactory
//todo 2. copy my functions to checking conditions
//todo 3. check validity of these functions
//todo 4. remove the existing conditions by mine
//todo 5a. add recursive invoking of calling operator 

//todo 6. remove ugly {} where we could do it
namespace NumericStorm
{
namespace Fitting
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
    virtual bool operator()(SimplexFigure<parameter_size>& figure) override
    {
        switch (m_curr_operation)
        {
        case "reflection":
            if (reflectionDecision(figure)) {
                figure[m_settings.getSecondWorstInd()] = figure.getReflected();
                return reset();
                //NOTE 5b. we need to check that in both cases expansion and reflection of returned reflection type
            }

            if (expansionCondition(figure))
                m_curr_operation = "expansion";
            else
                m_curr_operation = "contraction";
            return true;
            break;
        case "expansion":
            if (expansionDecision(figure))
                figure[m_settings.getWorstInd()] = figure.getFinal();
            else
                figure[m_settings.getWorstInd()] = figure.getReflected();
            return reset();
            break;
        case "contraction":
            if (contractionDecision(figure)) {
                figure[m_settings.getWorstInd()] = figure.getFinal();
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
    const bool contractionDecision(NumericStorm::Fitting::SimplexFigure<parameter_size>& figure)
    {
        return figure.getFinal() <= figure.getReflected();
    }
    const bool expansionDecision(NumericStorm::Fitting::SimplexFigure<parameter_size>& figure)
    {
        return figure.getFinal() < figure.getReflected();
    }
    const bool expansionCondition(NumericStorm::Fitting::SimplexFigure<parameter_size>& figure)
    {
        return figure.getReflected() < figure[m_settings.getBestInd()];
    }
    const bool reflectionDecision(NumericStorm::Fitting::SimplexFigure<parameter_size>& figure)
    {
        return figure[m_settings.getBestInd()] <= figure.getReflected() && figure.getReflected() < figure[m_settings.getSecondWorstInd()];
    }
    /*
    virtual bool operator()(SimplexFigure<parameter_size>& figure) override
    {


    }
    */
    const std::string& getOperation() const { return m_curr_operation; }
    bool reset() { m_curr_operation = "reflection"; return false; }

private:
    std::string m_curr_operation{ "reflection" };

};
}

}