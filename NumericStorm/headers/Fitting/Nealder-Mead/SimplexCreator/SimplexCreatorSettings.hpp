
#pragma once
#include <string>
namespace NumericStorm 
{
namespace Fitting 
{
class SimplexCreatorSettigns 
{
public:
	SimplexCreatorSettigns() = default;
	SimplexCreatorSettigns(const SimplexCreatorSettigns&) = default;
	SimplexCreatorSettigns(SimplexCreatorSettigns&&) = default;
	SimplexCreatorSettigns& operator=(const SimplexCreatorSettigns&) = default;
	SimplexCreatorSettigns& operator=(SimplexCreatorSettigns&&) = default;

	virtual ~SimplexCreatorSettigns() = default;

	SimplexCreatorSettigns(std::string operationName, double mu)
		: m_name{ operationName }, m_mu{ mu } {}

	const std::string& getName() const { return m_name; }
	double getMu() const { return m_mu; }
private:
	std::string m_name{};
	double m_mu{};
};
}

}