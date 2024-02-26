#pragma once
#include "ISimplexOperation.hpp"
#include "SimplexOperationSettigns.hpp"
#include "../SimplexFigure.hpp"


namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size>
class Reflection : public ISimplexOperation<parameter_size>
{
public:
	Reflection(const SimplexOperationSettigns& settings)
		:ISimplexOperation<parameter_size>("reflection", settings) {};

	virtual SimplexFigure<parameter_size> operator ()(const SimplexFigure<parameter_size>& simplexFigure) override;


};

template <size_t parameter_size>
SimplexFigure<parameter_size> Reflection<parameter_size>::operator()(const SimplexFigure<parameter_size>& simplexFigure)
{

	double alpha = this->m_settings.getFactor();
	SimplexPoint<parameter_size>& centroid = simplexFigure.getCentroid();
	SimplexPoint<parameter_size>& pointToReflectArround(centroid);

	#if DEBUG
		auto difference = centroid - simplexFigure[0];
		auto multiplicated = difference * alpha;
		pointToReflectArround += multiplicated;
	#else if REALASE
		pointToReflectArround += (centroid - simplexFigure[0]) * alpha;
	#endif

		simplexFigure[0] = pointToReflectArround;
		return simplexFigure;
};


}
}