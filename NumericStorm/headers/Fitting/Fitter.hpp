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
	virtual Parameters<parameter_size>* getFittedParameters() = 0;
	virtual void minimize() = 0;
	virtual void setUp(FitterSettings<parameter_size>* fitterSettings) = 0;
protected:
	Parameters<parameter_size>* m_fittedParamters;
	Parameters<parameter_size>* m_proposedParameters;
	FitterSettings<parameter_size>* m_fitterSettings;

};

}
}

