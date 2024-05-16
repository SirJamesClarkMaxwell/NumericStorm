#pragma once

#include "SimplexSettings.hpp"
#include "StrategyManager.hpp"
#include "SimplexOperationsHeader.hpp"
#include "SimplexCreatorFactory.hpp"


namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size,class AxularyParameters=AdditionalParameters, class DerivedSettings = SimplexSettings<parameter_size>>
class SimplexFitter : public Fitter<parameter_size, AxularyParameters,DerivedSettings>
{

public:
	explicit SimplexFitter(DerivedSettings settings)
		:Fitter<parameter_size, AxularyParameters, DerivedSettings>{ settings,false } {}
	/*
		SimplexFitter(const SimplexFitter<parameter_size, DerivedSettings>&) = default;
		SimplexFitter(SimplexFitter<parameter_size, DerivedSettings>&&) = default;
		SimplexFitter<parameter_size, DerivedSettings>& operator=(const SimplexFitter<parameter_size, DerivedSettings>&) = default;
		SimplexFitter<parameter_size, DerivedSettings>& operator=(SimplexFitter<parameter_size, DerivedSettings>&&) = default;
	*/

	virtual ~SimplexFitter() = default;
protected:
	SimplexOperationFactory<parameter_size> m_simplexOperationFactory{};
	SimplexCreatorFactory<parameter_size> m_simplexCreatorFactory{};
	StrategyManager<parameter_size> m_strategyManager{};

};



}
}