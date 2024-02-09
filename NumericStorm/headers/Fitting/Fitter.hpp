#pragma once
#include "FitterSettings.hpp"
#include "Parameters.hpp"
namespace NumericStorm 
{
namespace Fitting 
{
template<size_t size_p>
class Fitter
{
public:
	Fitter <size_p>() = default;
	virtual Parameters<size_p>* getFittedParameters() = 0;
	virtual void minimize() = 0;
	virtual void setUp(FitterSettings<size_p>* fitterSettings) = 0;
protected:
	Parameters<size_p>* m_fittedParamters;
	Parameters<size_p>* m_proposedParameters;
	FitterSettings<size_p>* m_fitterSettings;

};

}
}

