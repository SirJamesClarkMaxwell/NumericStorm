#pragma once

#include "SimplexFigure.hpp"
#include "SimplexPoint.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
#include "../SimplexOperations/SimplexOperationsFactory.hpp"
#include "SimplexDecision/StrategyManager.hpp"
#include "SimplexCreator/SimplexCreatorFactory.hpp"
namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size>
class SimplexFitter :public Fitter<parameter_size>
{

public:
	SimplexFitter(const SimplexPoint<parameter_size>& initialPoint)
		:m_initialPoint(initialPoint) {};
	~SimplexFitter() {};
private:
	SimplexPoint<parameter_size> m_initialPoint;
	SimplexOperationFactory<parameter_size> m_simplexOperationFactory;
	SimplexCreatorFactory<parameter_size> m_simplexCreatorFactory;
	StrategyManager<parameter_size> m_strategyManager;

};
}
}