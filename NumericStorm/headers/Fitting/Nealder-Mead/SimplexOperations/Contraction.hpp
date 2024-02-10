#pragma once
#include "ISimplexOperation.hpp"
#include "../SimplexFigure.hpp"
#include "SimplexOperationArguments.hpp"
namespace NumericStorm
{
namespace Fitting
{
template<size_t figure_size> 
class Contraction :public ISimplexOperation<figure_size>
{
public:
	Contraction(const std::string& name,const SimplexFigure<figure_size> simplexFigure)
		:m_operationName(name),m_simplexFigure(simplexFigure){};
	SimplexFigure<figure_size> operation(const SimplexOperationArguments& argumetns) override;
private:
	SimplexPoint<figure_size - 1> decidePointToContraction(SimplexPoint<figure_size-1> reflectedPoint);
};

template<size_t figure_size>
SimplexFigure<figure_size> Contraction<figure_size>::operation(const SimplexOperationArguments& argumetns)
{
	SimplexFigure<figure_size> contractedFigure(m_simplexFigure);
	SimplexPoint<figure_size - 1> pointToContraction = decidePointToContraction();
	SimplexPoint<figure_size - 1> pointToContractArround; (contractedFigure.getCentroid());
	double factor = argumetns.getFactor();

	#if DEBUG
	auto difference = (pointToContraction - contractedFigure.getCentroid());
	auto multiplication = difference * factor;
	pointToContractArround += multiplication;
	#endif
	#if REALESE
	pointToContractArround += (pointToContraction - m_simplexFigure.getCentroid()) * factor;
	#endif
	
	contractedFigure[0] = pointToContractArround;

	return contractedFigure;
}

template<size_t figure_size>
SimplexPoint<figure_size - 1> Contraction<figure_size>::decidePointToContraction(SimplexPoint<figure_size-1> reflectedPoint)
{
	return reflectedPoint ? reflectedPoint <= m_simplexFigure[0] : m_simplexFigure[0];
}

}
}

