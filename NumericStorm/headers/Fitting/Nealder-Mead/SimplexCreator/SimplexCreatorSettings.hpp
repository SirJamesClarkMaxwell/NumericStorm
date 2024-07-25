#pragma once
#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"

namespace NumericStorm::Fitting
{
	template<size_t parameter_size>
	class SimplexCreatorSettings
	{
	public:
		using In = SimplexPoint<parameter_size>;
		using Out = SimplexFigure<parameter_size>;

		
		SimplexCreatorSettings(const Parameters<parameter_size>& min, const Parameters<parameter_size>& max)
			: m_minBounds{ min }, m_maxBounds{ max } {};
		
	
		virtual ~SimplexCreatorSettings() = default;
	
		Parameters<parameter_size>& getMinBounds() const
		{
			return m_minBounds;
		}
	
		Parameters<parameter_size>& getMaxBounds() const
		{
			return m_maxBounds;
		}
	
	protected:
		Parameters<parameter_size> m_minBounds{};
		Parameters<parameter_size> m_maxBounds{};
		
	};
}