#pragma once

namespace NumericStorm 
{
namespace Fitting 
{
template<size_t size_p>
class Fitter
{
public:
	Fitter() = default;
	~Fitter() {};
	virtual Parameters& <size_p> getFittedParameters() = 0;
	virtual minimize() = 0;
	virtual setUp(FitterSettings&<size_p> fitterSettings) = 0;
protected:
	Parameters& <size_p> m_fittedParamters;
	Parameters& <size_p> m_proposedParameters;
	FitterSettings& <size_p> m_fitterSettings;

};

}
}

