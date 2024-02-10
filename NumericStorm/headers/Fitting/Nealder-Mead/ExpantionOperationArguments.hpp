#pragma once
#include "SimplexOperationArguments.hpp"
#include "SimplexPoint.hpp"
namespace NumericStorm {
namespace Fitting {
template<size_t point_dimention>
class ExpantionOperationArguments :public SimplexOperationArguments 
{
public:
	ExpantionOperationArguments(const double& factor, const SimplexPoint<point_dimention> reflectedPoint ) 
		: SimplexOperationArguments(factor), m_reflectedPoint(reflectedPoint){}
	SimplexPoint<point_dimention> reflectedPoint;


};

}
}

