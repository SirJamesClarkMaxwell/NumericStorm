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
		using SettingsT = typename SimplexOperationBase<parameter_size>::SettingsT;

		Expansion() = default;

		Expansion(const SettingsT& settings)
			: SimplexOperationBase<parameter_size>{settings} {}

		typename SettingsT::Out operator()(typename SettingsT::In& state) override
		{
			const SimplexPoint<parameter_size>& centroid = state.getSimplexFigure().getCentroid();
			const SimplexPoint<parameter_size>& reflected = state[Reflected];
			SimplexPoint<parameter_size>& expanded = state[Expanded];
			double gamma = this->getSettings().getFactor();
	#if DEBUG
			auto difference = reflected - centroid;
			auto scaled = difference * gamma;
			expanded = centroid + scaled;
	#elif RELEASE
			expanded = centroid + (reflected - centroid) * gamma;
	#endif
			expanded.evaluatePoint();
			JFM_Trace();
		}
	};
} // namespace Fitting
} // namespace NumericStorm
