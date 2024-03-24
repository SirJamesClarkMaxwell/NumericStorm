#pragma once

#include "../SimplexFigure.hpp"
#include "../SimplexFitter.hpp"
#include "../SimplexPoint.hpp"
#include "BasicSimplexFitterSettings.hpp"
#include "../SimplexOperations/SimplexOperationsHeader.hpp"
// TODO: write BasicSimplexFitter to minimize implementation
namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size>
class BasicSimplexFitter : public SimplexFitter<parameter_size>
{
public:
	BasicSimplexFitter(const SimplexPoint<parameter_size>& initialPoint)
		: SimplexFitter<parameter_size>(initialPoint) {}

	void setUp(BasicSimplexFitterSettings<parameter_size> fitterSettings);
	void minimize(std::shared_ptr<Data> referenceData, double maxError, double maxIterations) override;

	Parameters<parameter_size> getFittedParameters() { return this->m_fittedParameters; };

};

template <size_t parameter_size>
void BasicSimplexFitter<parameter_size>::setUp(BasicSimplexFitterSettings<parameter_size> fitterSettigns)
{
	//TODO: implement setUp function
};
template <size_t parameter_size>
void BasicSimplexFitter<parameter_size>::minimize(std::shared_ptr<Data> referenceData, double maxError, double maxIterations)
{
	//TODO: implement minimize function
};
}