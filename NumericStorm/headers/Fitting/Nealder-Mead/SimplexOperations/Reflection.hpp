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
	Reflection()
		:ISimplexOperation<parameter_size>("reflection", SimplexOperationSettings{ 0.5 }) {};
	Reflection(const SimplexOperationSettings& settings)
		: ISimplexOperation<parameter_size>("reflection", settings) {};

	virtual void operator()(SimplexIntermediatePoints<parameter_size>& simplexIntPoints) override
	{
		double alpha = this->m_settings.getFactor();
		const SimplexPoint<parameter_size>& centroid = simplexIntPoints.getCentroid();
		SimplexPoint<parameter_size>& reflectedPoint = simplexIntPoints[Reflected];
		const SimplexPoint<parameter_size>& worstPoint = simplexIntPoints.m_simplexFigure[worstPoint];

#if DEBUG
		auto difference = centroid - worstPoint;
		auto scaled = difference * alpha;
		reflectedPoint = centroid + scaled;
#elif RELEASE
		reflectedPoint = centroid + (centroid - worstPoint) * alpha;
#endif
		reflectedPoint.evaluatePoint();

	}
};

}
}