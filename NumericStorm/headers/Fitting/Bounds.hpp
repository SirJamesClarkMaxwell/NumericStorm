#pragma once
#include "Fitting.hpp"

namespace NumericStorm
{
namespace Fitting
{
template<size_t bounds_size>
class Bounds :public Parameters<bounds_size>
{
public:
	Bounds(std::array<double, bounds_size> bounds)
		: Parameters<bounds_size>(bounds) {};

	virtual double& operator [](int index) = 0;
	virtual std::array<double, size_p> getParameters() = 0;

	virtual double getError() { return -1 };
	//TODO remove error
	virtual void setUp() = 0;

	virtual calculateError(const Data& referenceData) {};
};

}
}