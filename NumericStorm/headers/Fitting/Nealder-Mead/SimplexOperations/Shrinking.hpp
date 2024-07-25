#pragma once
#include <algorithm>

#include "SimplexOperationBase.hpp"

namespace NumericStorm::Fitting
{

    template <size_t parameter_size>
    class Shrinking : public SimplexOperationBase<parameter_size>
    {
    public:
    
        Shrinking(const SettingsT& settings)
            : SimplexOperationBase<parameter_size>{settings} {}
    
    
        typename SettingsT::Out operator()(typename SettingsT::In& state)
        {
            
            const SimplexPoint<parameter_size>& bestPoint = state.getBestPoint();
            double delta = getSettings().getFactor();
    

            std::for_each(state.getSimplexFigure().begin(), state.getSimplexFigure().end() - 1,
                [&](auto& shrunk) {
                    shrunk = bestPoint + (shrunk - bestPoint) * delta;
                    shrunk.evaluatePoint();
                });
    
        }
    };

}
