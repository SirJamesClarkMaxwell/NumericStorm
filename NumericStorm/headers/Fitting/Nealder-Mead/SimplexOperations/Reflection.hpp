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

	SimplexFigure<figure_size> operator()  (const SimplexOperationArguments& arguments) override;

};

template<size_t figure_size>
SimplexFigure<figure_size> Reflection<figure_size>::operator() (const SimplexOperationArguments& arguments)
{
	SimplexFigure<figure_size> reflectedFigure(m_simplexFigure);
	
	double alpha = arguments.getFactor();
	SimplexPoint<figure_size - 1> centroid = reflectedFigure.getCentroid();
	SimplexPoint<figure_size - 1> pointToReflectArround(centroid);
	#if DEBUG
		auto difference = centroid - reflectedFigure[0];
		auto multiplicated = difference * alpha;
		auto pointToReflectArround += multiplicated;
	#else if REALASE
	pointToReflectArround += (centroid - reflectedFigure[0]) * alpha;
	#endif

		reflectedFigure[0] = pointToReflectArround;
		return reflectedFigure;
			
		

}

}
}