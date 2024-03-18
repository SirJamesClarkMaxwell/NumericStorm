#pragma once
#include "SimplexOperationSettigns.hpp"
#include "ISimplexOperation.hpp"
#include "../SimplexFigure.hpp"
#include "../SimplexPoint.hpp"

namespace NumericStorm
{
    namespace Fitting
    {
        template <size_t parameter_size>
        class Shrinking : public ISimplexOperation<parameter_size>
        {
        public:

            Shrinking(const SimplexOperationSettings &settings)
                : ISimplexOperation<parameter_size>("shrinking", settings){}


            SimplexFigure<parameter_size>& operator()(SimplexFigure<parameter_size>& simplexFigure) override {
                double delta = this->m_settings.getFactor();

                //best point is the last one
                SimplexPoint<parameter_size>& bestPoint = simplexFigure[parameter_size];

                for (size_t i = 0; i < parameter_size; ++i)
                    simplexFigure[i] = bestPoint + (simplexFigure[i] - bestPoint) * delta;

                return simplexFigure;
            }
        };

    }
}
