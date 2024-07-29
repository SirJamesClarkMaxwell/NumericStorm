#pragma once

#include "Parameters.hpp"

namespace NumericStorm::Fitting {
	template<size_t parameter_size>
	struct SimplexOptimizationResults
	{
	public:
		using WrappedStateT = void;

	SimplexOptimizationResults() = default;

	auto& getParameters() { return m_parameters; }
	const auto& getParameters() const { return m_parameters; }

	auto& getError() { return m_error; }
	const auto& getError() const { return m_error; }

	auto& getIteration() { return m_iteration; }
	const auto& getIteration() const { return m_iteration; }

	WrappedStateT getWrappedState() const {}

	protected:
		Parameters<parameter_size> m_parameters{};
		double m_error{ 0.0 };
		long int m_iteration{ 0 };
	};
}