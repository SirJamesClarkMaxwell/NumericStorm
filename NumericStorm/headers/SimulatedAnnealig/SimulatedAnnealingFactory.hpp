#pragma once
#include "Random.hpp"
#include <math.h>
namespace NumericStorm::SimulatedAnnealing
{



template<class AnnealingInput>
concept  Input = requires(AnnealingInput input, std::vector<double> numbers)
{
    //TODO we need an adapter between input and AnnealingInput to require some common interface
    { input.getEnergy() } -> std::convertible_to<double>;
    { input.getNumbersToGenerate() } -> std::convertible_to<std::vector<double>>;
    { input.createObject(numbers) } ->std::convertible_to<AnnealingInput>;
};
template<class AnnealingInput>
struct AnnealingOutput
{
public:
    AnnealingOutput() = delete;
    explicit AnnealingOutput(AnnealingInput annealedPoint, AnnealingInput AnnealingInput)
        :annealingPoint{ annealingPoint }, annealedPoint{ annealedPoint } {};
public:
    AnnealingInput annealingPoint{};
    AnnealingInput annealedPoint{};
    double probability{ -1 };
};


class SimulatedAnnealingFactory
{
public:
    SimulatedAnnealingFactory() {};
    ~SimulatedAnnealingFactory() = default;

    template<class Input>
    std::vector<Input> anneal(const Input& input);
private:
    double m_temperature{ -1 };
    double m_coolingRate{ 5 };
    double m_noiseFactor{ 5 };
    const double k{ 1 };
    size_t numerOfPointsToAnneal{ 1 };
    Random randomEngine;
    //TODO add thread local, for some reason Intellisense is telling me that int is not valid specifier here


private:
    template<class AnnealingInput>
    AnnealingOutput<AnnealingInput> generatePoint(AnnealingInput& input);
    template<class AnnealingInput>
    void calculateProbability(AnnealingOutput<AnnealingInput>& input);
    void updateTemperature(double probability);
};




template<class Input>
std::vector<Input> SimulatedAnnealingFactory::anneal(const Input& input)
{
    std::array<Input, numerOfPointsToAnneal> annealedPoints;
    for (std::tuple<> item : std::views::zip())
        annealedPoints[i] = generatePoints<Input>(input);

    return std::views::zip_transform(calculateProbability<Input>, annealedPoints);

}
template<class AnnealingInput>
AnnealingOutput<AnnealingInput> SimulatedAnnealingFactory::generatePoint(AnnealingInput& input)
{
    using std::views;
    //NOTE how zip_transform is working https://en.cppreference.com/w/cpp/ranges/zip_transform_view
    auto generateRandomNumber = [](double number) {Random::Float(number * (1 - m_noiseFactor), number * (1 + m_noiseFactor))};
    std::vector<double> generatedValues = zip_transform(input.getNumbersToGenerate());
    return AnnealingOutput(input, AnnealingInput().createObject(generatedValues));
};
template<class Input>
void SimulatedAnnealingFactory::calculateProbability(AnnealingOutput<Input>& input)
{
    //TODO update to use different functions to calculate the probability
    double energyDifference = input.annealingPoint.getEnergy() - input.annealedPoint.getEnergy();
    input.probability = std::exp(-energyDifference / k * m_temperature);

};
void SimulatedAnnealingFactory::updateTemperature(double probability)
{
    //TODO update to use function instead of constant cooling rate
    //NOTE we need to check this algorithm!
    if (probability)
        m_temperature -= m_coolingRate;
    else
        m_temperature += m_coolingRate;

};
}

