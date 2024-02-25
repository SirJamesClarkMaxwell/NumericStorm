#pragma once
#include "ISimplexOperation.hpp"
#include "../SimplexFigure.hpp"
#include "SimplexOperationArguments.hpp"

namespace NumericStorm
{
namespace Fitting
{

template <size_t parameter_size>
class Contraction : public ISimplexOperation<parameter_size>
{
public:
	Contraction(const SimplexOperationArguments& arguments)
		:ISimplexOperation("contraction", arguments) {};
	SimplexFigure<parameter_size> operator()(const SimplexFigure<parameter_size>& reflectedSimplexFigure);

private:
	SimplexPoint<parameter_size> decidePointToContraction(SimplexFigure<parameter_size> reflectedFigure);
	std::string m_operationName;
};
template <size_t parameter_size>
SimplexFigure<parameter_size> Contraction<parameter_size>::operator()(const SimplexFigure<parameter_size> & reflectedSimplexFigure)
{
	SimplexFigure<parameter_size>& contractedFigure(reflectedSimplexFigure);
	SimplexPoint<parameter_size>& reflectedPoint(reflectedSimplexFigure[0]);

	SimplexPoint<parameter_size>& pointToContraction = decidePointToContraction(reflectedSimplexFigure);
	SimplexPoint<parameter_size>& pointToContractArround(contractedFigure.getCentroid());

	double beta = this->m_arguments.getFactor();

	#if DEBUG
		auto difference = (pointToContraction - pointToContractArround);
		auto multiplication = difference * beta;
		pointToContractArround += multiplication;
	#endif

	#if REALESE
		pointToContractArround += (pointToContraction - pointToContractArround) * beta;
	#endif

	contractedFigure[0] = pointToContractArround;
	return contractedFigure;
}


template <size_t parameter_size>
SimplexPoint<parameter_size> Contraction<parameter_size>::decidePointToContraction(SimplexFigure<parameter_size> reflectedFigure)
{
	SimplexPoint<parameter_size>& reflectedPoint = reflectedFigure[0];
	SimplexPoint<parameter_size>& secondBestPoint = reflectedFigure[1];
	return  (reflectedPoint <= secondBestPoint) ? reflectedPoint: secondBestPoint;
}


}
}
