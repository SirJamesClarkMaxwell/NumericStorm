#pragma once

#include "../SimplexFigure.hpp"
#include "../SimplexFitter.hpp"
#include "../SimplexPoint.hpp"


namespace NumericStorm 
{
namespace Fitting 
{
template<size_t figure_size>
class BasicSimplexFitter:public SimplexFitter<figure_size>
{
public:
	BasicSimplexFitter(SimplexFigure<figure_size> simplexFigure) 
		:SimplexFitter<figure_size>(simplexFigure){}


};

}
}