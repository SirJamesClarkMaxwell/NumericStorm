#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexOperationArguments.hpp"
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
	double alpha = arguments.getFactor();
	SimplexPoint<figure_size - 1> centroid = this->m_simplexFigure.getCentroid();
	this->m_simplexFigure.sort();
	#if DEBUG
		auto difference = centroid - this->m_simplexFigure[0];
		auto multiplicated = difference * alpha;
		auto reflectedPoint = centroid + multiplicated;
	#else if REALASE
		SimplexPoint<figure_size - 1> reflectedPoint = centroid + (centroid - this->m_simplexFigure[0]) * alpha;
	#endif

		this->m_simplexFigure[0] = reflectedPoint;
		return this->m_simplexFigure;
			
		

}

}
}