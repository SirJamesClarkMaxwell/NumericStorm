#pragma once

namespace NumericStorm::Fitting
{

class SimplexOperationSettings
{
public:
	SimplexOperationSettings(double factor)
		: m_factor{ factor } {}
	SimplexOperationSettings() = default;
	SimplexOperationSettings(const SimplexOperationSettings&) = default;
	SimplexOperationSettings(SimplexOperationSettings&&) = default;
	SimplexOperationSettings& operator=(const SimplexOperationSettings&) = default;
	SimplexOperationSettings& operator=(SimplexOperationSettings&&) = default;
	virtual ~SimplexOperationSettings() = default;
	double getFactor() const { return m_factor; }

protected:
	double m_factor{};
};
}