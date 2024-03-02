#pragma once

namespace NumericStorm
{
	namespace Fitting
	{

		class SimplexOperationSettings
		{
		public:
			SimplexOperationSettings(double factor)
				: m_factor(factor){};
			double getFactor() { return m_factor; }

		protected:
			double m_factor;
		};
	}
}