#pragma once
#include "SimplexOperationArguments.hpp"
#include "../SimplexPoint.hpp"
namespace NumericStorm {
namespace Fitting {

template<size_t point_dimention>
class ReflectionOperationArguments :public SimplexOperationArguments
{
public:
	ReflectionOperationArguments(const double& factor)
		: SimplexOperationArguments(factor){}

};
}
}

