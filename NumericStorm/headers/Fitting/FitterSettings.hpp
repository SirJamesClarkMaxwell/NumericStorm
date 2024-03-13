#pragma once

#include "Model.hpp"
#include "ErrorModel.hpp"
#include <memory>
#include <functional>

namespace NumericStorm 
{
namespace Fitting 
{
template <size_t parameter_size>
class FitterSettings
{
public:
	FitterSettings() = delete;
	FitterSettings(const FitterSettings<parameter_size>&) = default;
	FitterSettings(FitterSettings<parameter_size>&&) = default;
	FitterSettings<parameter_size>& operator=(const FitterSettings<parameter_size>&) = default;
	FitterSettings<parameter_size>& operator=(FitterSettings<parameter_size>&&) = default;

	virtual ~FitterSettings() = default;

	FitterSettings(const Model<parameter_size>& model, const ErrorModel& errorModel, const AdditionalParameters& add_params, long int maxIteration,double minError)
		: m_functionModel{ model }, m_errorModel{ errorModel }, m_maxIteration{ maxIteration }, m_minError{ minError }, m_add_params{ add_params } {}

	//there is no reason for this to be an abstract class since all the methods return data defined in this very class
	virtual const Model<parameter_size>& getFunctionModel() { return m_functionModel; };
	virtual const ErrorModel& getErrorModel() { return m_errorModel; }
	virtual double getMinError() { return m_minError; }
	virtual long int getMaxIteration() { return m_maxIteration; }
protected:
	AdditionalParameters m_add_params{};
	Model<parameter_size> m_functionModel;
	ErrorModel m_errorModel;
	long int m_maxIteration{};
	double m_minError{};
};

}

}