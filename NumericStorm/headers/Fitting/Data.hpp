#pragma once

#include <vector>


namespace NumericStorm::Fitting
{
class Data
{
public:
	Data() = default;
	Data(unsigned int dimension) { m_data.resize(dimension); };
	Data(const Data&) = default;
	Data(Data&&) = default;
	Data& operator=(const Data&) = default;
	Data& operator=(Data&&) = default;
	std::vector<double>& operator[](size_t index) {
		return m_data.at(index);
	};
	const std::vector<double>& operator[](size_t index) const {
		return m_data.at(index);
	};

	virtual ~Data() = default;
protected:
	std::vector<std::vector<double>> m_data{};
};



}