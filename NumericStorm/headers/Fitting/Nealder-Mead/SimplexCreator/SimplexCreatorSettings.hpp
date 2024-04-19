#pragma once
#include <string>

namespace NumericStorm::Fitting
{
class SimplexCreatorSettings
{
public:
	SimplexCreatorSettings() = default;
	SimplexCreatorSettings(const SimplexCreatorSettings&) = default;
	SimplexCreatorSettings(SimplexCreatorSettings&&) = default;
	SimplexCreatorSettings& operator=(const SimplexCreatorSettings&) = default;
	SimplexCreatorSettings& operator=(SimplexCreatorSettings&&) = default;

	virtual ~SimplexCreatorSettings() = default;

	SimplexCreatorSettings(std::string operationName, double mu)
		: m_name{ operationName }, m_mu{ mu } {}

	const std::string& getName() const { return m_name; }
	double getMu() const { return m_mu; } //NU what is this???
private:
	std::string m_name{};
	double m_mu{};
};
}