#pragma once

#include "SimplexFigure.hpp"
#include "SimplexPoint.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
#include "SimplexSettings.hpp"
#include "./SimplexDecision/StrategyManager.hpp"
#include "./SimplexOperations/SimplexOperationsHeader.hpp"
#include "./SimplexCreator/SimplexCreatorFactory.hpp"


namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size, class DerivedSettings = FitterSettings<parameter_size>>
class SimplexFitter : public Fitter<parameter_size, DerivedSettings>
{

public:
	SimplexFitter() = default;
	SimplexFitter(const SimplexFitter<parameter_size, DerivedSettings>&) = default;
	SimplexFitter(SimplexFitter<parameter_size, DerivedSettings>&&) = default;
	SimplexFitter<parameter_size, DerivedSettings>& operator=(const SimplexFitter<parameter_size, DerivedSettings>&) = default;
	SimplexFitter<parameter_size, DerivedSettings>& operator=(SimplexFitter<parameter_size, DerivedSettings>&&) = default;

	virtual ~SimplexFitter() = default;
	SimplexFitter(const SimplexSettings<parameter_size>& simplexSettings)
		: Fitter<parameter_size, DerivedSettings>{ simplexSettings } {};

protected:
	SimplexOperationFactory<parameter_size> m_simplexOperationFactory{};
	SimplexCreatorFactory<parameter_size> m_simplexCreatorFactory{};
	StrategyManager<parameter_size> m_strategyManager{};

};



}
}