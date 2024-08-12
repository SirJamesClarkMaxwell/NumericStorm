#pragma once

#include "Optimizer.hpp"

namespace NumericStorm::Fitting {

using namespace NumericStorm::Concepts;


	

	template<Optimizer OptimizerT>
	class Fitter
	{
	public:
		explicit Fitter(const OptimizerT& optimizer, bool calculateUncertainty = false)
			: m_optimizer{ optimizer } {};
	
		typename OptimizerT::SettingsT::OptimizerOutputT fit(const typename OptimizerT::SettingsT::OptimizerInputT& initialParameters, const Data& fittingData,
			const typename OptimizerT::SettingsT::AuxilaryParametersT& additionalParameters) {

			auto state = m_optimizer.setUpOptimization(initialParameters, fittingData, additionalParameters);
			while (!m_optimizer.checkStop(state)) {
				m_optimizer.oneStep(state);
			}
				

			/*if (m_calculateUncertainty)
				std::vector<std::vector<double>> uncertainty = m_uncertaintyCalculator(m_optimizer.getResults());*/

			return m_optimizer.getResults(state);
		}
	
	
		//void setUncertaintyCalculator(UncertaintyStrategyWrapper uncertaintyCalculator) { m_uncertaintyCalculator = uncertaintyCalculator; };
	
		virtual ~Fitter() = default;


	private:
		OptimizerT m_optimizer;
		//UncertaintyCalculator m_uncertaintyCalculator;
	};
	
}



