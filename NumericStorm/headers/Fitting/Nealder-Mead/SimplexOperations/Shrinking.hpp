#pragma once
#include "SimplexOperationSettigns.hpp"
#include "ISimplexOperation.hpp"
#include "../SimplexFigure.hpp"
#include "../SimplexPoint.hpp"


namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size>
class Shrinking : public ISimplexOperation<parameter_size>
{
public:
	Shrinking(const SimplexOperationSettigns& settings)
		: ISimplexOperation<parameter_size>("shrinking", settings) {};
	SimplexFigure<parameter_size> operator()(const SimplexFigure<parameter_size>& simplexFigure) override;
};

template <size_t parameter_size>
SimplexFigure<parameter_size> Shrinking<parameter_size>::operator()(const SimplexFigure<parameter_size> &simplexFigure)
{
    double delta = this->m_settings.getFactor();
    
    SimplexFigure<parameter_size> result = simplexFigure;
    const SimplexPoint<parameter_size>& bestPoint = simplexFigure[0];

   for (size_t i = 1; i < parameter_size + 1; ++i) 
        result[i] = bestPoint + (simplexFigure[i] - bestPoint) * delta;
 
    return result;
}

}
}
