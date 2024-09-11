#pragma once

#include "Optimizer.hpp"
#include <mutex>



static std::mutex g_ErrorMutex;
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
			std::vector<double> errors{};
			auto state = m_optimizer.setUpOptimization(initialParameters, fittingData, additionalParameters);
			while (!m_optimizer.checkStop(state)) {
				m_optimizer.oneStep(state);
				errors.push_back(state.getBestPoint().getError());
			}
			g_ErrorMutex.lock();
			//globalErrors.push_back(errors);
			g_ErrorMutex.unlock();

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



