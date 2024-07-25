#pragma once

#include "SimplexIntermediateState.hpp"
#include "BasicOperationsEnum.hpp"
#include "BasicSimplexIndeciesEnum.hpp"

namespace NumericStorm::Fitting
{
	template<size_t parameter_size>
	class SimplexOperationSettings
	{
	public:
		using In = SimplexIntermediateState<parameter_size, BasicSimplexIndeciesEnum, BasicOperationsEnum>;
		using Out = void;
	
		SimplexOperationSettings(double factor)
			: m_factor{ factor } {}
		
		virtual ~SimplexOperationSettings() = default;
	
		double getFactor() const { return m_factor; }
		void setFactor(double factor) { m_factor = factor; }
	
	
	protected:
		double m_factor{};
	};
}