#pragma once

#include "Fitting.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
template<size_t size_p>
class SimplexFitter :public Fitter<size_p>
{

public:
	SimplexFitter() = default;
	~SimplexFitter() {};
protected:
	SimplexFigure<size_p + 1> m_simplexFigure;

};
}
}