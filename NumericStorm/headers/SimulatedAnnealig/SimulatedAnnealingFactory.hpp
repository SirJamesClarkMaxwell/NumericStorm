#pragma once
#include "Random.hpp"
namespace NumericStorm::SimulatedAnnealing
{

class SimulatedAnnealingFactory
{
public:
    SimulatedAnnealingFactory() {};
    ~SimulatedAnnealingFactory() = default;

    template<class Input, class Output>
    Output anneal(Input input);
private:
    double m_temperature{ -1 };
    double m_coolingRate{ 5 };
    double m_noiseFactor{ 5 };
    size_t numerOfPointsToAnneal{ 1 };
    template<class Input, class Output>
    Output generatePoint(Input input);
    double calculateProbability();
    void updateTemperature();
};




template<class Input, class Output>
Output SimulatedAnnealingFactory::anneal(Input input)
{
    return Output();
}
template<class Input, class Output>
Output SimulatedAnnealingFactory::generatePoint(Input input) {};
double SimulatedAnnealingFactory::calculateProbability() {};
void SimulatedAnnealingFactory::updateTemperature() {};
}

