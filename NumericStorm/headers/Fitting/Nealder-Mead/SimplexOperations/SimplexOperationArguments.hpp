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
	const double getFactor() const { return m_factor; }
protected:
	double m_factor;

};
}
}