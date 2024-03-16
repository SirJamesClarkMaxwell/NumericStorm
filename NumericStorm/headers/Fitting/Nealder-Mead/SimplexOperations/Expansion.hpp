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
public:
	Expansion(const SimplexOperationSettings& settings)
		: ISimplexOperation<parameter_size>("expansion", settings) {};

	SimplexFigure<parameter_size> operator()(SimplexFigure<parameter_size>& reflectedSimplexFigure) override;

private:
	std::string m_operationName;
};

template <size_t parameter_size>
SimplexFigure<parameter_size> Expansion<parameter_size>::operator()(SimplexFigure<parameter_size>& reflectedSimplexFigure)
{
	SimplexFigure<parameter_size>& expandedFigure(reflectedSimplexFigure);
	SimplexPoint<parameter_size>& reflectedPoint = reflectedSimplexFigure[0];
	SimplexPoint<parameter_size>& pointToExpandAround(expandedFigure.getCentroid());
	double gamma = this->m_settings.getFactor();

#if DEBUG
	auto centroid = expandedFigure.getCentroid();
	auto difference = reflectedPoint - centroid;
	auto multipled = difference * gamma;
	pointToExpandAround += multipled;

#else if REALESE
	pointToExpandAround += (reflectedPoint - centroid) * gamma;
#endif
	expandedFigure[0] = pointToExpandAround;
	return expandedFigure;
}

}
}