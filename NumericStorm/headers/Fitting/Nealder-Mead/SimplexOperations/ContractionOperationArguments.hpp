#pragma once
#include "SimplexOperationArguments.hpp"
#include "../SimplexFigure.hpp"
namespace NumericStorm 
{
namespace Fitting 
{
template <size_t figure_size>
class ContractionOperationArguments : public SimplexOperationArguments
{
public:
	ContractionOperationArguments(double factor,
		const SimplexFigure<figure_size>& simplexFigure,
		const SimplexPoint<figure_size -1>& reflectedPoint)
		:m_factor(factor),m_simplexFigure(simplexFigure),m_reflectedPoint(reflectedPoint){}
private:
	SimplexPoint<figure_size - 1> m_reflectedPoint;
	SimplexFigure<figure_size> m_simplexFigure;

};

}
}