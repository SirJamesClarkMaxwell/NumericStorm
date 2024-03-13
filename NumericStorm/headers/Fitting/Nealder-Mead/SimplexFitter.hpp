#pragma once

#include "SimplexFigure.hpp"
#include "SimplexPoint.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
#include "SimplexSettings.hpp"


namespace NumericStorm 
{
namespace Fitting 
{
template<size_t parameter_size, class DerivedSettings = SimplexSettings<parameter_size>>
class SimplexFitter : public Fitter<parameter_size, DerivedSettings>
{

public:
	SimplexFitter() = default;
	SimplexFitter(const SimplexFitter<parameter_size, DerivedSettings>&) = default;
	SimplexFitter(SimplexFitter<parameter_size, DerivedSettings>&&) = default;
	SimplexFitter<parameter_size, DerivedSettings>& operator=(const SimplexFitter<parameter_size, DerivedSettings>&) = default;
	SimplexFitter<parameter_size, DerivedSettings>& operator=(SimplexFitter<parameter_size, DerivedSettings>&&) = default;

	virtual ~SimplexFitter() = default;

	SimplexFitter(const SimplexFigure<parameter_size>& simplexFigure)
		: Fitter{}, m_simplexFigure{ simplexFigure } {};
protected:
	SimplexFigure<parameter_size> m_simplexFigure{};
};
}
}