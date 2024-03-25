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
	//todo redefine this class to be parameterized by the returning type of calling operator -> SimplexPoint
public:
	//todo add default things, but maybe it is defined i ISimplexOperation

	Reflection(const SimplexOperationSettings& settings)
		: ISimplexOperation<parameter_size>("reflection", settings) {};

	virtual SimplexFigure<parameter_size>& operator()(SimplexFigure<parameter_size>& simplexFigure) override {
		double alpha = this->m_settings.getFactor();
		const SimplexPoint<parameter_size>& centroid = simplexFigure.getCentroid();
		SimplexPoint<parameter_size>& reflectedPoint = simplexFigure.getReflected();
		const SimplexPoint<parameter_size>& worstPoint = simplexFigure[0];

#if DEBUG
		auto difference = centroid - worstPoint;
		auto scaled = difference * alpha;
		reflectedPoint = centroid + scaled;
#elif RELEASE
		reflectedPoint = centroid + (centroid - worstPoint) * alpha;
#endif
		return simplexFigure;
	}
};

}
}