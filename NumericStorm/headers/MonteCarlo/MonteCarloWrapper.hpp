#pragma once

#include "MonteCarlo.hpp"
#include "Optimizer.hpp"
#include "Data.hpp"
#include "MonteCarloCPUExecutor.hpp"


namespace NumericStorm::MonteCarlo
{
using namespace NumericStorm::Concepts;
using namespace NumericStorm::Fitting;

	template<Optimizer O>
	class MonteCarloWrapper
	{
	public:
		MonteCarloWrapper(const MonteCarloSettings& settings) : m_monteCarlo{ settings } {}
		
		std::vector<std::vector<double>> calculateUncertainty(const O& optimizer, const typename O::SettingsT::OptimizerInputT& input, const Data& data, const typename O::SettingsT::AuxParameters& addPar) {
			auto results = m_monteCarlo.runSimulations(optimizer, input, data, addPar);

			//calculate uncertainty
		}

	private:
		MonteCarlo<MonteCarloCPUExecutor, O> m_monteCarlo{};
	};

};