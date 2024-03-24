
#pragma once
#include <string>
namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size>
class SimplexCreatorSettings
{
public:
	SimplexCreatorSettings(std::string operationName, const SimplexPoint<parameter_size>& minBounds, const SimplexPoint<parameter_size>& maxBounds)
		:m_name(operationName), m_minBounds(minBounds), m_maxBounds(maxBounds) {};
private:
	std::string m_name;
	SimplexPoint<parameter_size> m_minBounds;
	SimplexPoint<parameter_size> m_maxBounds;

};
}

}