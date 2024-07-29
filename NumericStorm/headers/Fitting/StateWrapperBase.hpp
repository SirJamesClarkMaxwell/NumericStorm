#pragma once

#include "OptimizerStateWrapper.hpp"

namespace NumericStorm::Fitting {
	using namespace NumericStorm::Concepts;

	template<OptimizerStateWrapper WrappedState>
	class StateWrapperBase
	{
	public:
		using WrappedStateT = WrappedState;

		StateWrapperBase(const WrappedStateT& state)
			: m_state{ state } {}

		WrappedStateT& getWrappedState() { return m_state; }
		const WrappedStateT& getWrappedState() const { return m_state; }

	protected:
		WrappedStateT m_state{};
	};
};