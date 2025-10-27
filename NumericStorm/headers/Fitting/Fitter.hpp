#pragma once
#include "Optimizer.hpp"
#include "utils.hpp"

namespace NumericStorm::Fitting {
	using namespace NumericStorm::Concepts;

	template<Optimizer OptimizerT>
	class Fitter
	{
	public:
		explicit Fitter(const OptimizerT& optimizer, bool calculateUncertainty = false)
			: m_optimizer{ optimizer } {};

		typename OptimizerT::SettingsT::OptimizerOutputT fit(
			const typename OptimizerT::SettingsT::OptimizerInputT& initialParameters,
			const Data& fittingData,
			const typename OptimizerT::SettingsT::AuxilaryParametersT& additionalParameters)
		{
			auto state = m_optimizer.setUpOptimization(initialParameters, fittingData, additionalParameters);

			while (!m_optimizer.checkStop(state))
			{
				m_optimizer.oneStep(state);
			}

			return m_optimizer.getResults(state);
		}

		virtual ~Fitter() = default;

	private:
		OptimizerT m_optimizer;
		//UncertaintyCalculator m_uncertaintyCalculator;
	};
} // namespace NumericStorm::Fitting
