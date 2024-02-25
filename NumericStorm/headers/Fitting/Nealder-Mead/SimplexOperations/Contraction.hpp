#pragma once
#include "ISimplexOperation.hpp"
#include "../SimplexFigure.hpp"
#include "ContractionOperationArguments.hpp"
#include "SimplexOperationArguments.hpp"
// TODO: redefine interface of Contraction

namespace NumericStorm
{
	namespace Fitting
	{
		template <size_t figure_size>
		class Contraction : public ISimplexOperation<figure_size>
		{
		public:
			Contraction(const std::string &name, const SimplexFigure<figure_size> simplexFigure)
				: ISimplexOperation(name, simplexFigure){};
			SimplexFigure<figure_size> operator()(const ContractionOperationArguments<figure_size - 1> &argumetns);

		private:
			SimplexPoint<figure_size - 1> decidePointToContraction(SimplexPoint<figure_size - 1> reflectedPoint);

			std::string m_operationName = "contraction";
		};

		template <size_t figure_size>
		SimplexFigure<figure_size> Contraction<figure_size>::operator()(const ContractionOperationArguments<figure_size - 1> &argumetns)
		{
			SimplexFigure<figure_size> contractedFigure(this->m_simplexFigure);
			SimplexPoint<figure_size - 1> pointToContraction = decidePointToContraction();
			SimplexPoint<figure_size - 1> pointToContractArround;
			(contractedFigure.getCentroid());
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

		template <size_t figure_size>
		SimplexPoint<figure_size - 1> Contraction<figure_size>::decidePointToContraction(SimplexPoint<figure_size - 1> reflectedPoint)
		{
			return reflectedPoint ? reflectedPoint <= this->m_simplexFigure[0] : this->m_simplexFigure[0];
		}

	}
}
