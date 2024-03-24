#pragma once
#include "FitterSettings.hpp"
#include "Parameters.hpp"
namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size>
class Fitter
{
public:
	Fitter() {};// = default;
	//virtual Parameters<parameter_size>* getFittedParameters() = 0;
	virtual void minimize(std::shared_ptr<Data> referenceData, double maxError, double maxIterations) = 0;
	//TODO: add logic of bounds -> SimplexFitter -> BasicSimplexFitter


};

}
}

