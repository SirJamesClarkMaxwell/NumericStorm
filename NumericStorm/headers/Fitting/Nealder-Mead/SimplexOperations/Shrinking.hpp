#pragma once
#include "SimplexOperationSettings.hpp"
#include "ISimplexOperation.hpp"
#include "SimplexFigure.hpp"
#include "SimplexPoint.hpp"
#include "SimplexIntermediatePoints.hpp"

namespace NumericStorm::Fitting
{

template <size_t parameter_size>
class Shrinking : public ISimplexOperation<parameter_size>
{
public:

    Shrinking()
        : ISimplexOperation<parameter_size>("shrinking", SimplexOperationSettings{ 0.5 }) {}
    Shrinking(const SimplexOperationSettings& settings)
        : ISimplexOperation<parameter_size>("shrinking", settings) {}
    virtual void operator()(SimplexIntermediatePoints<parameter_size>& simplexIntPoints) override
    {
        double delta = this->m_settings.getFactor();
        const SimplexPoint<parameter_size>& bestPoint = simplexIntPoints[parameter_size];

#if DEBUG

        for (size_t i = 0; i < parameter_size - 1; ++i)
        {
            auto& shrinked = simplexIntPoints.m_simplexFigure[i];
            auto difference = shrinked - bestPoint;
            auto scaled = difference * delta;
            shrinked = bestPoint + scaled;
            shrinked.evaluatePoint();
        }
#else if RELEASE
        for (size_t i = 0; i < parameter_size - 1; ++i)
        {
            //todo refactor to work with iterators of simplexFigure
            simplexIntPoints.m_simplexFigure[i] = bestPoint + (simplexIntPoints.m_simplexFigure[i] - bestPoint) * delta;
            point.evaluatePoint();
        }
#endif

    }
};

}
