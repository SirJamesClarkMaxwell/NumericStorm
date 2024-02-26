#pragma once

namespace NumericStorm 
{
namespace Fitting
{

class SimplexOperationSettigns
{
public:
	SimplexOperationSettigns(double factor)
		:m_factor(factor) {};
	double getFactor() { return m_factor; }
protected:
	double m_factor;

};
}
}