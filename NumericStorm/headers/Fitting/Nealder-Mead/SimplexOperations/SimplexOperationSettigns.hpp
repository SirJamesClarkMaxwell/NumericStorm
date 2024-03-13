#pragma once

namespace NumericStorm
{
	namespace Fitting
	{

		class SimplexOperationSettings
		{
		public:
			SimplexOperationSettings() = default;
			SimplexOperationSettings(const SimplexOperationSettings&) = default;
			SimplexOperationSettings(SimplexOperationSettings&&) = default;
			SimplexOperationSettings& operator=(const SimplexOperationSettings&) = default;
			SimplexOperationSettings& operator=(SimplexOperationSettings&&) = default;

			virtual ~SimplexOperationSettings() = default;

			SimplexOperationSettings(double factor)
				: m_factor{ factor } {}

			double getFactor() const { return m_factor; }

		protected:
			double m_factor{};
		};
	}
}