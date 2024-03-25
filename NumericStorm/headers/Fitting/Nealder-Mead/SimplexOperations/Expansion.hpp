#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexOperationSettigns.hpp"
#include "../SimplexFigure.hpp"

// TODO: redefine interface of Expansion
namespace NumericStorm
{
namespace Fitting
{

template <size_t parameter_size>
class Expansion : public ISimplexOperation<parameter_size>
{
	//todo redefine this class to be parameterized by the returning type of calling operator -> SimplexPoint
public:
	Expansion(const SimplexOperationSettings& settings)
		: ISimplexOperation<parameter_size>("expansion", settings) {};

	SimplexFigure<parameter_size>& operator()(SimplexFigure<parameter_size>& reflectedSimplexFigure) override
	{
		const SimplexPoint<parameter_size>& centroid = reflectedSimplexFigure.getCentroid();
		SimplexPoint<parameter_size>& expanded = reflectedSimplexFigure.getFinal();
		const SimplexPoint<parameter_size>& reflected = reflectedSimplexFigure.getReflected();
		double gamma = this->m_settings.getFactor();
#if DEBUG
		auto difference = reflected - centroid;
		auto scaled = difference * gamma;
		expanded = centroid + scaled;
#elif RELEASE
		expanded = centroid + (reflected - centroid) * gamma;
#endif
		return reflectedSimplexFigure;
	}

};

}
}