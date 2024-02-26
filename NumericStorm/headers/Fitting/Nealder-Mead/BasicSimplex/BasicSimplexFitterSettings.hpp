#pragma once

#include <memory>
#include "../SimplexSettings.hpp"
#include "../../Model.hpp"
#include "../../ErrorModel.hpp"
#include "../SimplexOperations/SimplexOperationsHeader.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
template<size_t parameter_size>
class BasicSimplexFitterSettings :SimplexSettings<parameter_size> 
{
public:
	BasicSimplexFitterSettings(std::unique_ptr<Model<parameter_size>> model, std::unique_ptr<ErrorModel> errorModel, long int maxIteration, double minError,double alpha,double beta,double gamma,double delta)
		:SimplexSettings<parameter_size> (model,errorModel,maxIteration,minError),
		m_alpha(alpha),m_beta(beta),m_gamma(gamma),m_delta(delta){};
private:
	double m_alpha;
	double m_beta;
	double m_gamma;
	double m_delta;

};


}
}