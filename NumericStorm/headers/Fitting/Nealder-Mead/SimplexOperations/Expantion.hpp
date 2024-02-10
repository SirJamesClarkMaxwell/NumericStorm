#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexOperationArguments.hpp"
#include "../SimplexFigure.hpp"
namespace NumericStorm 
{
namespace Fitting 
{

template<size_t figure_size>
class Expantion :public ISimplexOperation<figure_size> 
{
public:
	Expantion(const std::string& name = "Expantion", SimplexFigure<figure_size> simplexFigure)
		:m_operationName(name), m_simplexFigure(simplexFigure) {};
	SimplexFigure<figure_size> operation(SimplexOperationArguments arguments)override;
};

template<size_t figure_size>
SimplexFigure<figure_size> Expantion<figure_size>::operation(SimplexOperationArguments arguments)
{
	SimplexFigure<figure_size> expandedFigure(m_simplexFigure);
	expandedFigure.sort();
	SimplexPoint<figue_size - 1> reflectedPoint = arguments.reflectedPoint;
	SimplexPoint<figure_size - 1> expandedPoint;

	#if DEBUG
	auto centroid = m_simplexFigure.getCentroid();
	auto difference = reflectedPoint - centroid;
	auto multipled = difference * arguments.getFactor();
	expandedPoint = centroid + multipled;

	#else if REALESE
	expandedPoint = centroid + (reflectedPoint - centroid) * arguments.getFactor();
	#endif
	expandedFigure[0] = expandedPoint;
	return expandedFigure;
}

}
}