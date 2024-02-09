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
	SimpelexFitter<size_p>() = default;
	~SimplexFitter<size_p>() {};
protected:
	SimplexFigure<size_p + 1> m_simplexFigure;

};
}
}