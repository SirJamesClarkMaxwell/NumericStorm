#pragma once

#include <memory>
#include "../SimplexSettings.hpp"
#include "../../Model.hpp"
#include "../../ErrorModel.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
template<size_t parameter_size>
class BasicSimplexSettings :SimplexSettings<parameter_size> 
{
	BasicSimplexSettings(std::unique_ptr<Model<parameter_size>> model, std::unique_ptr<ErrorModel> errorModel, long int maxIteration, double minError)
		:SimplexSettings<parameter_size> (model,errorModel,maxIteration,minError) {};
};

}
}