#pragma once
#include "SimplexOperationBase.hpp"

namespace NumericStorm
{
namespace Fitting
{

	template <size_t parameter_size>
	class Expansion : public SimplexOperationBase<parameter_size>
	{
	public:
	
		Expansion(const SettingsT& settings)
			: SimplexOperationBase<parameter_size>{settings} {}
	
		typename SettingsT::Out operator()(typename SettingsT::In& state)
		{
			const SimplexPoint<parameter_size>& centroid = state.getSimplexFigure().getCentroid();
			const SimplexPoint<parameter_size>& reflected = state[Reflected];
			SimplexPoint<parameter_size>& expanded = state[Expanded];
			
			double gamma = getSettings().getFactor();
	#if DEBUG
			auto difference = reflected - centroid;
			auto scaled = difference * gamma;
			expanded = centroid + scaled;
	#elif RELEASE
			expanded = centroid + (reflected - centroid) * gamma;
	#endif
			expanded.evaluatePoint();
		}
	
	};

}
}