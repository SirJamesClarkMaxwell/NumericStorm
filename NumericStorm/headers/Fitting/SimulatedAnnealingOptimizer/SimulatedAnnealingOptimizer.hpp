#pragma once

#include "Optimizer.hpp"
#include "Data.hpp"
#include "AnnealingOptimizerSettings.hpp"
#include "BasicSimulatedAnnealing.hpp"


namespace NumericStorm::Fitting
{
using namespace NumericStorm::Concepts;
using namespace NumericStorm::Annealing;

template <Optimizer OptimizerT>
class SimulatedAnnealingOptimizer
{
public:
	using SettingsT = AnnealingOptimizerSettings<typename OptimizerT::SettingsT>;
	using AdapterT = typename OptimizerT::AdapterT;

	using AnnealingT = typename SettingsT::AnnealingT;

	SimulatedAnnealingOptimizer(const SettingsT& settings)
		: m_settings{ settings }, m_optimizer{ settings.getWrappedSettings() }, m_annealing{ settings.getAnnealingSettings() } {}


	virtual ~SimulatedAnnealingOptimizer() = default;


	void setUp()
	{
		m_optimizer.setUp();
	};

	bool checkStop(const typename SettingsT::OptimizerStateT& state) const
	{
		return m_optimizer.checkStop(state.getWrappedState());
	}

	typename SettingsT::OptimizerStateT setUpOptimization(const typename SettingsT::OptimizerInputT& input, const Data& data, const typename SettingsT::AuxParameters& additionalParameters)
	{
		auto state = m_optimizer.setUpOptimization(input, data, additionalParameters);
		typename  SettingsT::OptimizerStateT annealingState{ state };

		AdapterT::adapt(annealingState);
		m_annealing.setUp(annealingState);

		return annealingState;
	};

	void oneStep(typename SettingsT::OptimizerStateT& state)
	{
		m_optimizer.oneStep(state.getWrappedState());
		m_annealing.anneal(state);
	};

	typename SettingsT::OptimizerOutputT getResult(const typename SettingsT::OpitmizerStateT& state) const
	{
		typename SettingsT::OptimizerOutputT result{ m_optimizer.getResult(state.getWrappedState()) };
		return result;
	};


private:
	SettingsT m_settings{};
	OptimizerT m_optimizer{};

	AnnealingT m_annealing{};

};


}
