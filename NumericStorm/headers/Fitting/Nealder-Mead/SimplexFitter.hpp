#pragma once

#include "SimplexFigure.hpp"
#include "SimplexPoint.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"


namespace NumericStorm 
{
namespace Fitting 
{
template<size_t figure_size>
class SimplexFitter :public Fitter<figure_size-1>
{

public:
	SimplexFitter(SimplexFigure<figure_size> simplexFigure)
		:m_simplexFigure(simplexFigure) {};
	~SimplexFitter() {};
protected:
	SimplexFigure<figure_size> m_simplexFigure;


};
}
}