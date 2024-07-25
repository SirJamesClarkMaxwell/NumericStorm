#pragma once
#include "SimplexOperationBase.hpp"

namespace NumericStorm::Fitting
{

	template <size_t parameter_size>
	class Contraction : public SimplexOperationBase<parameter_size>
	{
	public:
		
		Contraction(const SettingsT& settings)
			: SimplexOperationBase<parameter_size>{settings} {}
	

		typename SettingsT::Out operator()(typename SettingsT::In& state) {
			
	
			const SimplexPoint<parameter_size>& centroid = state.getSimplexFigure().getCentroid();
			const SimplexPoint<parameter_size>& pointToContractAround = decidePointToContractAround(state);
			SimplexPoint<parameter_size>& contracted = state[Contracted];
			double beta = getSettings().getFactor();
	
	#if DEBUG
			auto difference = (pointToContractAround - centroid);
			auto scaled = difference * beta;
			contracted = centroid + scaled;
	#elif RELEASE
			contracted = centroid + (pointToContractAround - centroid) * beta;
	#endif
			contracted.evaluatePoint();
		}
	
	
	private:
		const auto& decidePointToContractAround(const typename SettingsT::In& state) const {
	
			const auto& reflectedPoint = state[Reflected];
			const auto& worst = state.getWorstPoint();
	
			return (reflectedPoint <= worst) ? reflectedPoint : worst;
		}
	};

}
