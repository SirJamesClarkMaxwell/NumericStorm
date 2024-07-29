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

template <OptimizerSettings Settings, class AT>
class BasicSimplexOptimizer : public SimplexOptimizerBase<Settings>
{
public:
	using SettingsT = Settings;
	using AdapterT = AT;



	BasicSimplexOptimizer(const SettingsT& settings)
		: SimplexOptimizerBase<SettingsT>{ settings } {}


	virtual ~BasicSimplexOptimizer() = default;


	void setUp()
	{
		m_simplexOperationVisitor.registerOperations(this->m_settings.getOperationSettings());
		m_strategy.updateSettings(this->m_settings.getStrategySettings());
		m_simplexCreator.updateSettings(this->m_settings.getCreatorSettings());
	};

	bool checkStop(const typename SettingsT::OptimizerStateT& state) const
	{
		return state.getIteration() > this->m_settings.getMaxIteration() 
			|| (state.getBestPoint().getError() > -1 
			&& state.getBestPoint().getError() < this->m_settings.getMinError());
	}

	typename SettingsT::OptimizerStateT setUpOptimization(const typename SettingsT::OptimizerInputT& input, const Data& data, const typename SettingsT::AuxilaryParametersT& additionalParameters)
	{

		SimplexPoint<SettingsT::parameter_size> inputPoint{ input };
		inputPoint.getData() = data;
		inputPoint.onEvaluate([&](SimplexPoint<SettingsT::parameter_size>& point) {
			this->m_settings.getModel()(point.getData(), point.getParameters(), additionalParameters);
			point.setError(this->m_settings.getErrorModel()(point.getData(), data));
			});

		auto pointCount = SimplexStrategySettings<SettingsT::parameter_size>::indecies::Count;
		typename SettingsT::OptimizerStateT state{ m_simplexCreator(inputPoint), pointCount };

		return state;
	};

	void oneStep(typename SettingsT::OptimizerStateT& state)
	{
		do {
			state.getSimplexFigure().sort();
			m_simplexOperationVisitor.visit(state.getCurrentOperation(), state);
		} while (m_strategy(state));

		std::cout << state.getIteration() << " " << state.getBestPoint().getError() << std::endl;
		for(auto& p : state.getBestPoint().getParameters())
			std::cout << p << " ";
		std::cout << std::endl;

		state.getIteration()++;
		
	};

	typename SettingsT::OptimizerOutputT getResults(const typename SettingsT::OptimizerStateT& state) const
	{
		typename SettingsT::OptimizerOutputT output{};
		output.getParameters() = state.getBestPoint().getParameters();
		output.getError() = state.getBestPoint().getError();
		output.getIteration() = state.getIteration();
		return output;
	};


private:
	BasicSimplexStrategy<SettingsT::parameter_size> m_strategy{};
	BasicSimplexCreator<SettingsT::parameter_size> m_simplexCreator{};
	SimplexOperationVisitor<SettingsT::parameter_size, typename SimplexStrategySettings<SettingsT::parameter_size>::operation_l> m_simplexOperationVisitor{};
};

template<Model M, class Adapter>
using BasicSimplexOptimizerM = BasicSimplexOptimizer<BasicSimplexOptimizerSettings<M>, Adapter>;


}