#pragma once

namespace NumericStorm 
{
namespace Fitting 
{
class SimplexOperationArguments 
{
public:
	SimplexOperationArguments(double factor)
		:m_factor(factor) {};
	double getFactor() { return m_factor; }
private:
	double m_factor;

};

}
}