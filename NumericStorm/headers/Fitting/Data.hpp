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
	Data() = delete;
	Data(unsigned int dimension) { m_data.resize(dimension); };
	Data(const Data&) = default;
	Data(Data&& d) = default;
	Data& operator=(const Data& d) = default;
	Data& operator=(Data&& d) = default;
	std::vector<double>& operator[](size_t index);
	const std::vector<double>& operator[](size_t index) const;

	virtual ~Data() = default;
protected:
	std::vector<std::vector<double>> m_data{};
};

std::vector<double>& Data::operator[](size_t index)
{
	return m_data.at(index);
};

const std::vector<double>& Data::operator[](size_t index) const 
{
	return m_data.at(index);
};

}
}