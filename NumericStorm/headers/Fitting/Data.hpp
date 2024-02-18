#pragma once

#include <vector>
#include "Fitting.hpp"
namespace NumericStorm 
{
namespace Fitting
{
class Data 
{
public:
	Data() = default;
	Data(const std::vector<double>& arguments,const std::vector<double>& values) 
		:m_argumets(arguments),m_values(values) {}
	virtual std::vector<double> getArguments() = 0;
	virtual std::vector<double> getValues() = 0;

protected:
	std::vector<double> m_argumets;
	std::vector<double> m_values;

};
}
}