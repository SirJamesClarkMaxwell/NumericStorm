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
	FitterSettings(std::shared_ptr<Model<parameter_size>> model, std::shared_ptr<ErrorModel> errorModel)
		:m_functionModel(model), m_errorModel(errorModel) {}
	virtual std::shared_ptr<Model<parameter_size>> getFunctionModel() = 0;
	virtual std::shared_ptr<ErrorModel> getErrorModel() = 0;
protected:
	std::shared_ptr<Model<parameter_size>> m_functionModel = nullptr;
	std::shared_ptr<ErrorModel> m_errorModel = nullptr;
};

}

}