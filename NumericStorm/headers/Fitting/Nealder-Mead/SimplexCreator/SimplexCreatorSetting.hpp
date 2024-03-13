
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

	SimplexCreatorSettigns(std::string operationName)
		: m_name{ operationName } {}

	const std::string& getName() const { return m_name; }
private:
	std::string m_name{};
};
}

}