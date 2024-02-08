#pragma once

#include "Fitting.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
template <size_t size_p>
class FitterSettings
{
public:
	FitterSettings() = default;
	FitterSettings(Model<size_p>& model,ErrorModel errorModel,long int maxIteration,double minError)
	:m_functionModel(model),m_errorModel(errorModel),m_maxIteration(maxIteration),m_minError(minError){}
	virtual Model<size_p>& getFunctionModel() = 0;
	virtual ErrorModel getErrorModel() = 0;
	virtual double getMinError() = 0;
	virtual long int getMaxIteration() = 0;
protected:
	Model<size_p>& m_functionModel;
	ErrorModel& m_errorModel;
	long int m_maxIteration;
	double m_minError;
};

}

}