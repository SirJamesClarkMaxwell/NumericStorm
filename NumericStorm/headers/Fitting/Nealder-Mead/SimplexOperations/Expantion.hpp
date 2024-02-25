#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexOperationArguments.hpp"
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
	Expantion(SimplexOperationArguments<parameter_size> arguments)
		: ISimplexOperation<parameter_size>("expantion", arguments) {};

	SimplexFigure<parameter_size> operator()(const SimplexFigure<parameter_size> &reflectedSimplexFigure) override;

private:
	std::string m_operationName = "expantion";
};

template <size_t parameter_size>
SimplexFigure<parameter_size> Expantion<parameter_size>::operator()(const SimplexFigure<parameter_size> &reflectedSimplexFigure)
{
	SimplexFigure<figure_size> expandedFigure(reflectedSimplexFigure);
	SimplexPoint<figure_size - 1> reflectedPoint = reflectedSimplexFigure[0];
	SimplexPoint<figure_size - 1> pointToExpandAround(expandedFigure.getCentroid());

	#if DEBUG
		auto centroid = expandedFigure.getCentroid();
		auto difference = reflectedPoint - centroid;
		auto multipled = difference * arguments.getFactor();
		pointToExpandAround += multipled;

	#else if REALESE
		pointToExpandAround += (reflectedPoint - centroid) * arguments.getFactor();
	#endif
		expandedFigure[0] = pointToExpandAround;
		return expandedFigure;
}


}
}