#pragma once
#include "ISimplexOperation.hpp"
#include "ReflectionOperationArguments.hpp"
#include "../SimplexFigure.hpp"
namespace NumericStorm {
namespace Fitting 
{
template<size_t parameter_size>
class Reflection :public ISimplexOperation<parameter_size> 
{

public:
	Reflection(const std::string& name, 
		const SimplexFigure<parameter_size>& simplexFigure)
		:ISimplexOperation<parameter_size>(name, simplexFigure) {};

	SimplexFigure<parameter_size> operator()  (const ReflectionOperationArguments<parameter_size>& arguments) override;
protected:
	std::string m_operationName = "reflection";
};

template<size_t parameter_size>
SimplexFigure<parameter_size> Reflection<parameter_size>::operator() (const ReflectionOperationArguments<parameter_size>& arguments)
{
	SimplexFigure<parameter_size> reflectedFigure(this->m_simplexFigure);
	
	double alpha = arguments.getFactor();
	SimplexPoint<parameter_size > centroid = reflectedFigure.getCentroid();
	SimplexPoint<parameter_size > pointToReflectArround(centroid);
	#if DEBUG
		auto difference = centroid - reflectedFigure[0];
		auto multiplicated = difference * alpha;	
		pointToReflectArround += multiplicated;
	#else if REALASE
	pointToReflectArround += (centroid - reflectedFigure[0]) * alpha;
	#endif

		reflectedFigure[0] = pointToReflectArround;
		return reflectedFigure;
}

}
}