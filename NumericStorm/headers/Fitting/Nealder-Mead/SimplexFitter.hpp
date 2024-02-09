#pragma once

#include "../Fitter.hpp"
#include "SimplexFigure.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
template<size_t parameter_size>
class SimplexFitter :public Fitter<parameter_size>
{

public:
	SimplexFitter(SimplexFigure<parameter_size+1> simplexFigure)
		:m_simplexFigure(simplexFigure) {};
	~SimplexFitter() {};
protected:
	SimplexFigure<parameter_size + 1> m_simplexFigure;

};
}
}