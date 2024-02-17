#pragma once

#include "../SimplexFigure.hpp"
#include "../SimplexFitter.hpp"
#include "../SimplexPoint.hpp"
#include "BasicSimplexFitterSettings.hpp"
#include "../SimplexOperations/SimplexOperationsHeader.hpp"

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

	void setUp(BasicSimplexSettings<figure_size-1> settigngs) override;
private:
	SimplexOperationFactory m_simplexOperationFactory;
};


template<size_t figure_size>
void BasicSimplexFitter<figure_size>::setUp(BasicSimplexSettings<figure_size - 1> settigngs)
{
	
};
}
}