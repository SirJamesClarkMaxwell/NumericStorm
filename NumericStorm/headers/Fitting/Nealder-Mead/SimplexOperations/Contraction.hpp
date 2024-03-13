#pragma once
#include "ISimplexOperation.hpp"
#include "../SimplexFigure.hpp"
#include "SimplexOperationSettigns.hpp"

namespace NumericStorm
{
	namespace Fitting
	{

		template <size_t parameter_size>
		class Contraction : public ISimplexOperation<parameter_size>
		{
		public:
			Contraction(const SimplexOperationSettings &arguments)
				: ISimplexOperation<parameter_size>("contraction", arguments) {}
			
			
			SimplexFigure<parameter_size+1>& operator()(SimplexFigure<parameter_size+1>& reflectedSimplexFigure) override {
				const SimplexPoint<parameter_size>& centroid = reflectedSimplexFigure.getCentroid();
				SimplexPoint<parameter_size>& contracted = reflectedSimplexFigure.getFinal();
				const SimplexPoint<parameter_size>& pointToContractAround = decidePointToContractAround(reflectedSimplexFigure);


				double beta = this->m_settings.getFactor();
				
			#if DEBUG
				auto difference = (pointToContractAround - centroid);
				auto scaled = difference * beta;
				contracted = centroid + scaled;
			#endif

			#if REALESE
				contracted = centroid + (pointToContractAround - centroid) * beta;
			#endif

				return reflectedSimplexFigure;
			}


		private:
			const SimplexPoint<parameter_size>& decidePointToContractAround(const SimplexFigure<parameter_size+1>& reflectedSimplexFigure) {
				const SimplexPoint<parameter_size>& reflectedPoint = reflectedSimplexFigure.getReflected();
				const SimplexPoint<parameter_size>& worst = reflectedSimplexFigure[0];
				return (reflectedPoint <= worst) ? reflectedPoint : worst;
			}
		};

	}
}
