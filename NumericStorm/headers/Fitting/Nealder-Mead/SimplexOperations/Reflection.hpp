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
			Reflection(const SimplexOperationSettings &settings)
				: ISimplexOperation<parameter_size>("reflection", settings){};

			virtual SimplexFigure<parameter_size+1>& operator()(SimplexFigure<parameter_size+1>& simplexFigure) override {
				double alpha = this->m_settings.getFactor();


				const SimplexPoint<parameter_size>& centroid = simplexFigure.getCentroid();
				//worst point is the first one
				SimplexPoint<parameter_size>& reflectedPoint = simplexFigure.getReflected();
				const SimplexPoint<parameter_size>& worstPoint = simplexFigure[0];

			#if DEBUG
				auto difference = centroid - worstPoint;
				auto scaled = difference * alpha;
				reflectedPoint = centroid + scaled;
			#elif RELEASE
				reflectedPoint = centroid + (centroid - worstPoint) * alpha;
			#endif

				return simplexFigure;
			}
		};

	}
}