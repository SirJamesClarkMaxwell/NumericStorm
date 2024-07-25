#pragma once

#include <memory>

#include "OptimizerSettings.hpp"
#include "SimplexOptimizerBase.hpp"
#include "BasicSimplexStrategy.hpp"
#include "BasicSimplexCreator.hpp"
#include "SimplexOperationVisitor.hpp"
#include "BasicSimplexOptimizerSettings.hpp"


namespace NumericStorm::Fitting
{
using namespace NumericStorm::Concepts;

template <OptimizerSettings Settings, class AdapterT>
class BasicSimplexOptimizer : public SimplexOptimizerBase<Settings>
{
public:
	using SettingsT = Settings;
	using AdapterT = AdapterT;
	BasicSimplexOptimizer(const SettingsT& settings)
		: SimplexOptimizerBase<SettingsT>{ settings } {}


	virtual ~BasicSimplexOptimizer() = default;


	void setUp()
	{
		m_simplexOperationVisitor.registerOperations(m_settings.getOperationSettings());
		m_strategy.updateSettings(m_settings.getStrategySettings());
		m_simplexCreator.updateSettings(m_settings.getCreatorSettings());
	};

	bool checkStop(const typename SettingsT::OptimizerStateT& state) const
	{
		return state.getIteration() >= m_settings.getMaxIteration() || state.getBestPoint().getError() <= m_settings.getMinError();
	}

	typename SettingsT::OptimizerStateT setUpOptimization(const typename SettingsT::OptimizerInputT& input, const Data& data, const typename SettingsT::AuxParameters& additionalParameters)
	{

		SimplexPoint<SettingsT::parameter_size> inputPoint{ input };
		inputPoint.getData() = data;
		inputPoint.onEvaluate([&](SimplexPoint<SettingsT::parameter_size>& point) {
			m_settings.getModel()(point.getData(), point.getParameters(), additionalParameters);
			point.setError(m_settings.getErrorModel()(point.getData(), data));
			});

		auto pointCount = SimplexStrategySettings<SettingsT::parameter_size>::indecies::Count;
		typename SettingsT::OptimizerStateT state{ m_simplexCreator(inputPoint), pointCount };

		return state;
	};

	void oneStep(typename SettingsT::OptimizerStateT& state)
	{
		while (m_strategy(state))
			m_simplexOperationVisitor.visit(state.getCurrentOperation(), state);
	};

	typename SettingsT::OptimizerOutputT getResult(const typename SettingsT::OpitmizerStateT& state) const
	{
		typename SettingsT::OptimizerOutputT output{};
		output.getParameters() = state.getBestPoint().getParameters();
		output.getError() = state.getBestPoint().getError();
		output.getIteration() = state.getIteration();
		return output;
	};


private:
	BasicSimplexStrategy<SettignsT::parameter_size> m_strategy{};
	BasicSimplexCreator<SettingsT::parameter_size> m_simplexCreator{};
	SimplexOperationVisitor<SettingsT::parameter_size, SimplexStrategySettings<parameter_size>::operation_l> m_simplexOperationVisitor{};
};

template<Model M>
using BasicSimplexOptimizerM = BasicSimplexOptimizer<BasicSimplexOptimizerSettings<M>>;


}