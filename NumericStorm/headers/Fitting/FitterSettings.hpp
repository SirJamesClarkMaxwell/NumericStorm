#pragma once

#include "Model.hpp"
#include "ErrorModel.hpp"
#include <memory>

namespace NumericStorm 
{
namespace Fitting 
{
template <size_t parameter_size>
class FitterSettings
{
public:
	FitterSettings(std::shared_ptr<Model<parameter_size>> model,std::shared_ptr<ErrorModel> errorModel,long int maxIteration,double minError)
	:m_functionModel(model),m_errorModel(errorModel),m_maxIteration(maxIteration),m_minError(minError){}
	virtual std::shared_ptr<Model<parameter_size>> getFunctionModel() = 0;
	virtual std::shared_ptr<ErrorModel> getErrorModel() = 0;
	virtual double getMinError() = 0;
	virtual long int getMaxIteration() = 0;
protected:
	std::shared_ptr<Model<parameter_size>> m_functionModel;
	std::shared_ptr<ErrorModel> m_errorModel;
	long int m_maxIteration;
	double m_minError;
};

}

}