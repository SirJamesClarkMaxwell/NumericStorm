#pragma once

#include <memory>
#include "../SimplexSettings.hpp"
#include "../../Model.hpp"
#include "../../ErrorModel.hpp"
#include "../SimplexOperations/SimplexOperationsHeader.hpp"
//todo we need to discus bout how we gonna implement the actual basic fitter
namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size>
class BasicSimplexFitterSettings :SimplexSettings<parameter_size>
{
public:
	BasicSimplexFitterSettings() = delete;
	BasicSimplexFitterSettings(const BasicSimplexFitterSettings<parameter_size>&) = default;
	BasicSimplexFitterSettings(BasicSimplexFitterSettings<parameter_size>&&) = default;
	BasicSimplexFitterSettings<parameter_size>& operator=(const BasicSimplexFitterSettings<parameter_size>&) = default;
	BasicSimplexFitterSettings<parameter_size>& operator=(BasicSimplexFitterSettings<parameter_size>&&) = default;

	virtual ~BasicSimplexFitterSettings() = default;

	BasicSimplexFitterSettings(const Model<parameter_size>& model, const ErrorModel& errorModel, long int maxIteration, double minError, double alpha, double beta, double gamma, double delta)
		: SimplexSettings<parameter_size>(model, errorModel, maxIteration, minError),
		m_alpha{ alpha }, m_beta{ beta }, m_gamma{ gamma }, m_delta{ delta } {};
	//BUG this parameters should be removed
	double getAlpha() const { return m_alpha; }
	double getBeta() const { return m_beta; }
	double getGamma() const { return m_gamma; }
	double getDelta() const { return m_delta; }

private:
	double m_alpha{};
	double m_beta{};
	double m_gamma{};
	double m_delta{};
	// todo think about the all possible settings of basic simplex fitter and set them manually
	//NOTE here we definitely need a builder pattern 
};


}
}