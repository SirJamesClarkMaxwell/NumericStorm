#pragma once
#include <array>
#include "Parameters.hpp"

namespace NumericStorm::Fitting
{
template<size_t bounds_size>
class Bounds :public Parameters<bounds_size>
{
public:
	Bounds(std::array<double, bounds_size> bounds)
		: Parameters<bounds_size>(bounds) {};

	virtual double& operator [](int index) = 0;
	virtual std::array<double, bounds_size> getParameters() = 0;
};

}