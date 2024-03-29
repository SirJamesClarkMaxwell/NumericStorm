#pragma once

#include <vector>
#include "Fitting.hpp"
namespace NumericStorm
{
namespace Fitting
{
template<size_t dimension>
class Data
{
public:
	Data() = default;
	Data(const Data<dimension>&) = default;
	Data(Data<dimension>&& d) = default;
	Data<dimension>& operator=(const Data<dimension>& d) = default;
	Data<dimension>& operator=(Data<dimension>&& d) = default;

	std::vector<double> operator[](size_t index) override throw(std::out_of_range);

	virtual ~Data() = default;
protected:
	std::array<std::vector<double>, dimension> m_data{};
};

template<size_t dimension>
std::vector<double> Data<dimension>::operator[](size_t index)
{
	if (index >= dimension or index < 0)
		throw std::out_of_range("Index out of range");
	return m_data[index];
};
}
}