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
	Data(const Data&) = default;
	Data(Data&& d) = default;
	Data& operator=(const Data& d) = default;
	Data& operator=(Data&& d) = default;
	std::vector<double> operator[](size_t index);

	virtual ~Data() = default;
protected:
	std::vector<std::vector<double>> m_data{};
};

std::vector<double> Data::operator[](size_t index)
{
	int dimension = m_data.size();
	if (index >= dimension or index < 0)
		throw std::out_of_range("Index out of range");
	return m_data[index];
};
}
}