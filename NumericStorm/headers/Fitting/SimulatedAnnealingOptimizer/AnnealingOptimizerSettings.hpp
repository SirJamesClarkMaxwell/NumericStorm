#pragma once

#include "OptimizerSettings.hpp"
#include "SimulatedAnnealingSetitngs.hpp"
#include "AnnealingOptimizerState.hpp"
#include "AnnealingOptimizerResults.hpp"

namespace NumericStorm::Fitting
{
using namespace NumericStorm::Concepts;

	template<OptimizerSettings S>
	class AnnealingOptimizerSettings
	{
	public:
		using parameter_size = S::parameter_size;
		using OptimizerInputT = S::OptimizerInputT;
		using OptimizerStateT = AnnealingOptimizerState<typename S::OptimizerStateT>;
		using OptimizerOutputT = AnnealingOptimizerResults;
		using AuxilaryParametersT = typename S::AuxilaryParameters;

		using AnnealingT = BasicSimulatedAnnealing;

		AnnealingOptimizerSettings(const S& settings)
			: m_settings{ settings } {}

		const S& getWrappedSettings() const { return m_settings; }

	private:
		S m_settings;
	};
};