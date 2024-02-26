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
class Expantion : public ISimplexOperation<parameter_size>
{
public:
	Expantion(SimplexOperationSettings arguments)
		: ISimplexOperation<parameter_size>("expantion", arguments) {};

	SimplexFigure<parameter_size> operator()(const SimplexFigure<parameter_size> &reflectedSimplexFigure) override;

private:
	std::string m_operationName = "expantion";
};

template <size_t parameter_size>
SimplexFigure<parameter_size> Expantion<parameter_size>::operator()(const SimplexFigure<parameter_size> &reflectedSimplexFigure)
{
	SimplexFigure<parameter_size>& expandedFigure(reflectedSimplexFigure);
	SimplexPoint<parameter_size>& reflectedPoint = reflectedSimplexFigure[0];
	SimplexPoint<parameter_size>& pointToExpandAround(expandedFigure.getCentroid());
	double gamma = this->m_arguments.getFactor();

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