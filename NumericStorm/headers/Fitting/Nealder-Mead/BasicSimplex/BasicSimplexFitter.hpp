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

	void setUp(FitterSettings<parameter_size>* fitterSettings) override;
	void minimize()override {};
	Parameters<parameter_size>* getFittedParameters() 
	{
		return m_fittedParameters;
	};
private:
	SimplexOperationFactory m_simplexOperationFactory;
};




template<size_t parameter_size>
inline void BasicSimplexFitter<parameter_size>::setUp(FitterSettings<parameter_size>* fitterSettings)
{
}

}
}