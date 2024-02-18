#pragma once

#include "SimplexFigure.hpp"
#include "SimplexPoint.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"


namespace NumericStorm 
{
namespace Fitting 
{
template<size_t parameter_size>
class SimplexFitter :public Fitter<parameter_size>
{

public:
	SimplexFitter(SimplexFigure<parameter_size> simplexFigure)
		:m_simplexFigure(simplexFigure) {};
	~SimplexFitter() {};
protected:
	SimplexFigure<parameter_size> m_simplexFigure;


};
}
}