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
	Data(const Data& d) = default;
	Data(Data&& d) = default;
	Data& operator=(const Data& d) = default;
	Data& operator=(Data&& d) = default;

	Data(const std::vector<double>& arguments = {}, const std::vector<double>& values = {})
		:m_argumets{ arguments }, m_values{ values } {}

	virtual ~Data() = default;
	virtual const std::vector<double>& getArguments() const = 0;
	virtual const std::vector<double>& getValues() const = 0;
	virtual void setArguments(const std::vector<double>& args) = 0;
	virtual void setValues(const std::vector<double>& vals) = 0;

protected:
	std::vector<double> m_argumets{};
	std::vector<double> m_values{};

};
}
}