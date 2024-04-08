#pragma once

#include "SimplexFigure.hpp"
#include "SimplexPoint.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
#include "SimplexSettings.hpp"
#include "./SimplexDecision/StrategyManager.hpp"
#include "./SimplexOperations/SimplexOperationsHeader.hpp"


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

	//NOTE constructor argument
	/*
	I am not sure that this is what we should do. The question is where we will have simplex creator
	as i wrote in Fitter class, I would pass the initial point into the minimize method,
	and create simplex inside the fitter based on some simplexCreator
	*/
	SimplexFitter(const SimplexFigure<parameter_size>& simplexFigure)
		: Fitter<parameter_size, DerivedSettings>{}, m_simplexFigure{ simplexFigure } {};
protected:
	SimplexFigure<parameter_size> m_simplexFigure{};

	StrategyManager<parameter_size> m_simplexStrategyFactory;
	SimplexOperationFactory<parameter_size> m_simplexOperationFactory;
	SimplexOperationFactory<parameter_size> m_simplexCreatorFactory;
};
}
}