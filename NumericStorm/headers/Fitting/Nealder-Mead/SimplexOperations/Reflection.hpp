#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexOperationSettigns.hpp"
#include "../SimplexFigure.hpp"

namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size>
class Reflection : public ISimplexOperation<parameter_size>
{
public:
	Reflection(const SimplexOperationSettings& settings)
		: ISimplexOperation<parameter_size>("reflection", settings) {};

	virtual SimplexFigure<parameter_size> operator()(SimplexFigure<parameter_size>& simplexFigure) override;
};

template <size_t parameter_size>
SimplexFigure<parameter_size> Reflection<parameter_size>::operator()(SimplexFigure<parameter_size>& simplexFigure)
{

	double alpha = this->m_settings.getFactor();
	SimplexPoint<parameter_size> centroid = simplexFigure.getCentroid();
	SimplexPoint<parameter_size> pointToReflectAround(centroid);

#if DEBUG
	auto difference = centroid - simplexFigure[0];
	auto multiplied = difference * alpha;
	pointToReflectAround += multiplied;
#else if REALASE
	pointToReflectAround += (centroid - simplexFigure[parameter_size]) * alpha;
#endif
	simplexFigure[0] = pointToReflectAround;
	return simplexFigure;
};

}
}