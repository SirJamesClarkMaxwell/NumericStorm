#pragma once

#include "OptimizerSettings.hpp"
#include "SimulatedAnnealingSetitngs.hpp"
#include "AnnealingOptimizerState.hpp"
#include "AnnealingOptimizerResults.hpp"
#include "BasicSimulatedAnnealing.hpp"

namespace NumericStorm::Fitting
{
using namespace NumericStorm::Concepts;
using namespace NumericStorm::Annealing;

	template<OptimizerSettings S>
	class AnnealingOptimizerSettings
	{
	public:
		static const int parameter_size = S::parameter_size;
		using OptimizerInputT = S::OptimizerInputT;
		using OptimizerStateT = AnnealingOptimizerState<typename S::OptimizerStateT>;
		using OptimizerOutputT = AnnealingOptimizerResults;
		using AuxilaryParametersT = typename S::AuxilaryParameters;

		using AnnealingT = BasicSimulatedAnnealing;

		AnnealingOptimizerSettings(const S& settings)
			: m_wrappedSettings{ settings } {}

		const S& getWrappedSettings() const { return m_wrappedSettings; }

		void setAnnealingSettings(const SimulatedAnnealingSettings& settings) { m_annealingSettings = settings; }
		auto& setAnnealingSettings() { return m_annealingSettings; }
		const auto& getAnnealingSettings() const { return m_annealingSettings; }

	private:
		S m_wrappedSettings;
		SimulatedAnnealingSettings m_annealingSettings{};
	};
};