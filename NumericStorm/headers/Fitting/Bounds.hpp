#pragma once
#include "Fitting.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
template<size_t size_b>
class Bounds :public Parameters<size_b>
{
public:
	Bounds(std::array<double, size_b> bounds)
		:Parameters<size_b>(bounds);

	virtual double& operator [](int index) = 0;
	virtual std::array<double, size_p> getParameters() = 0;

	virtual double getError() { return -1 };
	virtual void setUp() = 0;

	virtual calculateError(const Data& referanceData) {};
};

}
}