#pragma once

#include "SimplexSettings.hpp"
#include "StrategyManager.hpp"
#include "SimplexOperationsHeader.hpp"
#include "SimplexCreatorFactory.hpp"


namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters, class DerivedSettings = SimplexSettings<parameter_size>>
class SimplexFitter : public Fitter<parameter_size, AuxilaryParameters, DerivedSettings>
{

public:
	explicit SimplexFitter(DerivedSettings settings, bool calculateUncertainty = false)
		:Fitter<parameter_size, AuxilaryParameters, DerivedSettings>{ settings,calculateUncertainty } {}
	virtual ~SimplexFitter() = default;
protected:
	SimplexOperationFactory<parameter_size> m_simplexOperationFactory{};
	SimplexCreatorFactory<parameter_size> m_simplexCreatorFactory{};
	StrategyManager<parameter_size> m_strategyManager{};

	SimplexFigure<parameter_size> m_simplexFigure{};

};



}
}