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
class BasicSimplexFitter:public SimplexFitter<parameter_size>
{
public:
	BasicSimplexFitter(SimplexFigure<parameter_size> simplexFigure) 
		:SimplexFitter<parameter_size>(simplexFigure){}

	void setUp(BasicSimplexFitterSettings<parameter_size> fitterSettings);
	void minimize()override {};
	//TODO add function pointer into function that will define the actual logic of the algorithm
	Parameters<parameter_size> getFittedParameters() 
	{
		return this->m_fittedParameters;
	};
private:
	SimplexOperationFactory<parameter_size + 1> m_simplexOperationFactory;
};

template<size_t parameter_size>
void BasicSimplexFitter<parameter_size>::setUp(BasicSimplexFitterSettings<parameter_size> fitterSettigns)
{
}

}
}