#pragma once
#include <ranges>
#include <algorithm>
#include "Random.hpp"

#include "SimulatedAnnealingSetitngs.hpp"
#include "SimulatedAnnealingState.hpp"

namespace NumericStorm::Annealing
{
using namespace NumericStorm::Concepts;
using namespace NumericStorm::Utils;

class BasicSimulatedAnnealing
{
public:

	BasicSimulatedAnnealing(const SimulatedAnnealingSettings& settings)
		: m_settings{ settings } {}

	virtual ~BasicSimulatedAnnealing() = default;

	template <SimulatedAnnealingState State>
	void anneal(State& state) {
		
		std::for_each(state.getConfigurations().cbegin(), state.getConfigurations().cend() - state.getBackOffset(), [&](const std::vector<double*>& config, size_t index) {
			std::transform(config.cbegin(), config.cend() - state.getBackOffset(), state.getAnnealedConfigurations()[index].begin(), [&](const double* value) {
				return this->fluctuate(*value);
				});
			});

		std::for_each(state.getAnnealedConfigurations().cbegin(), state.getAnnealedConfigurations().cbegin() - state.getBackOffset(), [&](const std::vector<double>& config, size_t index) {
			state.getAnnealedEnergies()[index] = state.getEnergy(config);
			});

		size_t index{ 0 };
		for( auto& [newEnergy, oldEnergy] : std::views::zip(state.getAnnealedEnergies(), state.getEnergies())) {
			if(index >= m_settings.getNumberToAnneal()) break;

			if(newEnergy < *oldEnergy) accept(state, index++);
			else if(challenge(calculateProbability(&oldEnergy, newEnergy, state.getTemperature()))) accept(state, index++);
			else ++index;
		}

		updateTemperature(state.getTemperature());
	}

	template <SimulatedAnnealingState State>
	void setUp(const State& state) {
		state.getBackOffset() = state.getConfigurations().size() - m_settings.getNumberToAnneal();
		if(state.getBackOffset() >= state.getConfigurations().size()) state.getBackOffset() = 0;

		state.getAnnealedEnergies().resize(state.getEnergies().size());
		state.getAnnealedConfigurations().resize(state.getConfigurations().size());

		std::for_each(state.getAnnealedConfigurations().begin(), state.getAnnealedConfigurations().end() - state.getBackOffset(), [&](std::vector<double>& config) {
			config.resize(state.getConfigurations()[0].size());
			});
	}

private:
	double fluctuate(double input) const {
		return Random::Float(input * (1 - m_settings.getNoiseFactor()), input * (1 + m_settings.getNoiseFactor()));
	}

	bool challenge(double probability) const {
		return Random::Float(0, 1) < probability;
	}

	double calculateProbability(double originalEnergy, double newEnergy, double temperature) const {
		return std::exp(-(originalEnergy - newEnergy) / (m_settings.getK() * temperature));
	}

	void updateTemperature(double& temperature) {
		temperature -= m_settings.getCoolingRate();
		temperature = std::max(temperature, 0.0001);
	}

	template <SimulatedAnnealingState State>
	void accept(State& state, size_t index) {
		std::for_each(state.getConfigurations()[index].begin(), state.getConfigurations()[index].end() - state.getBackOffset(), [&](double* value, size_t i) {
			*value = state.getAnnealedConfigurations()[index][i];
			});

		std::for_each(state.getEnergies().begin(), state.getEnergies().end() - state.getBackOffset(), [&](double* value, size_t i) {
			*value = state.getAnnealedEnergies()[i];
			});

	}

private:
	SimulatedAnnealingSettings m_settings{};
};
}

