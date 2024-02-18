#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexOperationArguments.hpp"
#include "ExpantionOperationArguments.hpp"
#include "../SimplexFigure.hpp"
namespace NumericStorm 
{
namespace Fitting 
{

template<size_t figure_size>
class Expantion : public ISimplexOperation<figure_size> 
{
public:
	Expantion(const std::string& name, SimplexFigure<figure_size> simplexFigure)
		: ISimplexOperation(name, simplexFigure) {};
	SimplexFigure<figure_size> operator()(const ExpantionOperationArguments<figure_size - 1>& arguments);

protected:
	std::string m_operationName = "expantion";
};

template<size_t figure_size>
SimplexFigure<figure_size> Expantion<figure_size>::operator()(const ExpantionOperationArguments<figure_size - 1>& arguments)
{
	SimplexFigure<figure_size> expandedFigure(this->m_simplexFigure);

	SimplexPoint<figure_size - 1> reflectedPoint = arguments.reflectedPoint;
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