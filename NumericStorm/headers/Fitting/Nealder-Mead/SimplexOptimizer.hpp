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
class SimplexOptimizer
{
public:
	explicit SimplexOptimizer(DerivedSettings settings, bool calculateUncertainty = false)
		:m_settings{ settings }, m_calculateUncertainty{ calculateUncertainty } {}
	virtual ~SimplexOptimizer() = default;
protected:
	SimplexOperationFactory<parameter_size> m_simplexOperationFactory{};
	SimplexCreatorFactory<parameter_size> m_simplexCreatorFactory{};
	StrategyManager<parameter_size> m_strategyManager{};

	SimplexFigure<parameter_size> m_simplexFigure{};
	DerivedSettings m_settings;
	bool m_calculateUncertainty{ true };
};



}
}