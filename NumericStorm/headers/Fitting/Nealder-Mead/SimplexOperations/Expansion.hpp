#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexOperationSettigns.hpp"
#include "../SimplexFigure.hpp"

namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size>
class Expansion : public ISimplexOperation<parameter_size>
{
public:
	Expansion()
		: ISimplexOperation<parameter_size>("expansion", SimplexCreatorSettings{ 2 }) {};
	Expansion(const SimplexOperationSettings& settings)
		: ISimplexOperation<parameter_size>("expansion", settings) {};

	virtual void operator ()(SimplexIntermediatePoints<parameter_size>& simplexIntPoints) override
	{
		const SimplexPoint<parameter_size>& centroid = simplexIntPoints.m_simplexFigure.getCentroid();
		SimplexPoint<parameter_size>& expanded = simplexIntPoints[Expanded];
		const SimplexPoint<parameter_size>& reflected = simplexIntPoints[Reflected];
		double gamma = this->m_settings.getFactor();
#if DEBUG
		auto difference = reflected - centroid;
		auto scaled = difference * gamma;
		expanded = centroid + scaled;
#elif RELEASE
		expanded = centroid + (reflected - centroid) * gamma;
#endif
		expanded.evaluatePoint();
	}

};

}
}