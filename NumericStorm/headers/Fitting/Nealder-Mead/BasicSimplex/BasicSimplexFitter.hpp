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
template<size_t parameter_size>
class BasicSimplexFitter:public SimplexFitter<parameter_size+1>
{
public:
	BasicSimplexFitter(SimplexFigure<parameter_size+1> simplexFigure) 
		:SimplexFitter<parameter_size+1>(simplexFigure){}

	void setUp(FitterSettings<parameter_size> settigngs) override;
	void minimize()override {};
private:
	SimplexOperationFactory m_simplexOperationFactory;
};


template<size_t parameter_size>
void BasicSimplexFitter<parameter_size>::setUp(FitterSettings<parameter_size> settigngs) 
{
	
};
}
}