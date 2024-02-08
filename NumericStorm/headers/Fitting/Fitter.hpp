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

protected:
	Parameters&<size_p> fittedParamters;
	Parameters& <size_p> proposedParameters;
	

};

}
}

