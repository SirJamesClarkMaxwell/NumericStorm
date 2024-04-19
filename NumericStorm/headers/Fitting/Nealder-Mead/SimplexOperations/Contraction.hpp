#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexIntermediatePoints.hpp"
#include "SimplexOperationSettings.hpp"

namespace NumericStorm::Fitting
{

template <size_t parameter_size>
class Contraction : public ISimplexOperation<parameter_size>
{
public:
	Contraction()
		: ISimplexOperation<parameter_size>("contraction", SimplexOperationSettings{ 0.5 }) {}
	Contraction(const SimplexOperationSettings& arguments)
		: ISimplexOperation<parameter_size>("contraction", arguments) {}

	virtual void  operator()(SimplexIntermediatePoints<parameter_size>& simplexIntPoints) override {
		const SimplexPoint<parameter_size>& centroid = simplexIntPoints.m_simplexFigure.getCentroid();
		SimplexPoint<parameter_size>& contracted = simplexIntPoints[Contracted];
		const SimplexPoint<parameter_size>& pointToContractAround = decidePointToContractAround(simplexIntPoints);
		double beta = this->m_settings.getFactor();

#if DEBUG
		auto difference = (pointToContractAround - centroid);
		auto scaled = difference * beta;
		contracted = centroid + scaled;
#elif RELEASE
		contracted = centroid + (pointToContractAround - centroid) * beta;
#endif
		contracted.evaluatePoint();
	}


private:
	const SimplexPoint<parameter_size>& decidePointToContractAround(const SimplexIntermediatePoints<parameter_size>& simplexIntPoints) {
		const SimplexPoint<parameter_size>& reflectedPoint = simplexIntPoints[Reflected];
		const SimplexPoint<parameter_size>& worst = simplexIntPoints.m_simplexFigure[worstPoint];
		return (reflectedPoint <= worst) ? reflectedPoint : worst;
	}
};

}
