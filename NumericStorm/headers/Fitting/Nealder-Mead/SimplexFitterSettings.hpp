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
class SimplexFitterSettings :public FitterSettings<parameter_size>
{
	SimplexFitterSettings(std::unique_ptr<Model<parameter_size>> model, std::unique_ptr<ErrorModel> errorModel)
		:FitterSettings<parameter_size>(model, errorModel) {};
	virtual void setUpSimplexOperationFactory() = 0;
	virtual void setUpStrategyManager() = 0;
	virtual void setUpSimplexCreatorFactory() = 0;

};



}
}