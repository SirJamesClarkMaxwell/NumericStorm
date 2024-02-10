#pragma once
#include "ISimplexOperation.hpp"
#include "../SimplexFigure.hpp"
#include "../SimplexPoint.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
template<size_t figure_size>
class Shrinking :public ISimplexOperation<figure_size>
{
public: 
	Shrinking(const std::string& name,const SimplexFigure<figure_size>& simplexFigure)

};


}
}
