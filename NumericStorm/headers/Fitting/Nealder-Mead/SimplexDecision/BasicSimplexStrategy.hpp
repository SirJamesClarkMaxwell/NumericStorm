#include "IDecision.hpp"
#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"
#include <string>

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
                switch (m_curr_operation) {
                    case "reflection":
                        if (figure[m_settings.getBestInd()] <= figure.getReflected() && figure.getReflected() < figure[m_settings.getSecondWorstInd()]) {
                            figure[m_settings.getSecondWorstInd()] = figure.getReflected();
                            return reset();
                        }

                        if (figure.getReflected() < figure[m_settings.getBestInd()]) {
                            m_curr_operation = "expansion";
                        }
                        else {
                            m_curr_operation = "contraction";
                        }

                        return true;
                        break;
                    case "expansion":
                        if (figure.getFinal() < figure.getReflected()) {
                            figure[m_settings.getWorstInd()] = figure.getFinal();
                        }
                        else {
                            figure[m_settings.getWorstInd()] = figure.getReflected();
                        }

                        return reset();
                        break;
                    case "contraction":
                        if (figure.getFinal() <= figure.getReflected()) {
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
            const std::string& getOperation() const { return m_curr_operation; }
            bool reset() { m_curr_operation = "reflection"; return false; }
        
        private:
            std::string m_curr_operation{ "reflection" };
            
        };
    }

}