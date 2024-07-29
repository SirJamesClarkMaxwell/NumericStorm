#pragma once

#include "StateWrapperBase.hpp"
#include "OptimizerStateWrapper.hpp"


namespace NumericStorm::Fitting
{
	using namespace NumericStorm::Concepts;

	template<OptimizerStateWrapper WrappedState>
	class AnnealingOptimizerResults : public StateWrapperBase<WrappedState> {
	public:
		AnnealingOptimizerResults() = default;

		AnnealingOptimizerResults(const WrappedState& state)
			: StateWrapperBase<WrappedState>{ state } {}
	};
};