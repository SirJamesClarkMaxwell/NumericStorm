#pragma once

#include "Model.hpp"
#include "ErrorModel.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
template <size_t parameter_size>
class FitterSettings
{
public:
	FitterSettings(Model<parameter_size>* model,ErrorModel* errorModel,long int maxIteration,double minError)
	:m_functionModel(model),m_errorModel(errorModel),m_maxIteration(maxIteration),m_minError(minError){}
	virtual Model<parameter_size>& getFunctionModel() = 0;
	virtual ErrorModel getErrorModel() = 0;
	virtual double getMinError() = 0;
	virtual long int getMaxIteration() = 0;
protected:
	Model<parameter_size>& m_functionModel;
	ErrorModel& m_errorModel;
	long int m_maxIteration;
	double m_minError;
};

}

}