#pragma once
#include "SimplexOperationBase.hpp"

namespace NumericStorm::Fitting
{
	template <size_t parameter_size>
	class Reflection : public SimplexOperationBase<parameter_size>
	{
	public:
		
		Reflection(const SettingsT& settings)
			: SimplexOperationBase<parameter_size>{settings} {};
	
		typename SettingsT::Out operator()(typename SettingsT::In& state)
		{
			
			const SimplexPoint<parameter_size>& centroid = state.getSimplexFigure().getCentroid();
			const SimplexPoint<parameter_size>& wPoint = state.getWorstPoint();
			SimplexPoint<parameter_size>& reflected = state[Reflected];
			
			double alpha = getSettings().getFactor();
	
	#if DEBUG
			auto difference = centroid - wPoint;
			auto scaled = difference * alpha;
			reflected = centroid + scaled;
	#elif RELEASE
			reflected = centroid + (centroid - wPoint) * alpha;
	#endif
			reflected.evaluatePoint();
		}
	};

}