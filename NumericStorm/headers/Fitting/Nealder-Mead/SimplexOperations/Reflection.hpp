#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexOperationArguments.hpp"
#include "../SimplexFigure.hpp"
namespace NumericStorm {
namespace Fitting 
{
template<size_t figure_size>
class Reflection :public ISimplexOperation<figure_size> 
{
public:
	Reflection(const std::string& name="reflection", 
		const SimplexFigure<figure_size>& simplexFigure)
		:ISimplexOperation<figure_size>(name, simplexFigure) {};

	SimplexFigure<figure_size> operation  (const SimplexOperationArguments& arguments) override;

};

template<size_t figure_size>
SimplexFigure<figure_size> Reflection<figure_size>::operation (const SimplexOperationArguments& arguments)
{
	SimplexFigure<figure_size> reflectedFigure(m_simplexFigure);
	reflectedFigure.sort();
	double alpha = arguments.getFactor();
	SimplexPoint<figure_size - 1> centroid = reflectedFigure.getCentroid();

	#if DEBUG
		auto difference = centroid - reflectedFigure[0];
		auto multiplicated = difference * alpha;
		auto reflectedPoint = centroid + multiplicated;
	#else if REALASE
		SimplexPoint<figure_size - 1> reflectedPoint = centroid + (centroid - reflectedFigure[0]) * alpha;
	#endif

		reflectedFigure[0] = reflectedPoint;
		return reflectedFigure;
			
		

}

}
}