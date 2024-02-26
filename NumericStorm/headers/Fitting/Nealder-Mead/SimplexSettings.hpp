#pragma once
#include <memory>

#include "../FitterSettings.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
namespace NumericStorm 
{
namespace Fitting 
{
template<size_t parameter_size>
class SimplexSettings :public FitterSettings<parameter_size> 
{
	SimplexSettings(std::unique_ptr<Model<parameter_size>> model, std::unique_ptr<ErrorModel> errorModel, int maxIteration, double minError)
		:FitterSettings<parameter_size>(model,errorModel,maxIteration,minError){};


};



}
}