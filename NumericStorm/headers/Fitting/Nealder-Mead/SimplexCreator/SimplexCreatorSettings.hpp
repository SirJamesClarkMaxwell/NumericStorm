#pragma once
#include <string>
#include <random>
namespace NumericStorm::Fitting
{
class SimplexCreatorSettings
{
public:
	explicit SimplexCreatorSettings(std::string operationName, double expectedValue)
		: m_name{ operationName }, m_expectedValue{ expectedValue } {}
	/*
	SimplexCreatorSettings() = default;
	SimplexCreatorSettings(const SimplexCreatorSettings&) = default;
	SimplexCreatorSettings(SimplexCreatorSettings&&) = default;
	SimplexCreatorSettings& operator=(const SimplexCreatorSettings&) = default;
	SimplexCreatorSettings& operator=(SimplexCreatorSettings&&) = default;
	*/

	virtual ~SimplexCreatorSettings() = default;

	const std::string& getName() const { return m_name; }
	double getExpectedValue() const { return m_expectedValue; } //NU what is this???
private:
	std::string m_name{};
	double m_expectedValue{};
	//todo add more distribubion function to choose, not only gauss
};
}