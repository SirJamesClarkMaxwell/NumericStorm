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

	FitterSettings(const Model<parameter_size>& model, const ErrorModel& errorModel, const AdditionalParameters& add_params, long int maxIteration, double minError)
		: m_functionModel{ model }, m_errorModel{ errorModel }, m_maxIteration{ maxIteration }, m_minError{ minError }, m_add_params{ add_params } {}

	//there is no reason for this to be an abstract class since all the methods return data defined in this very class
	virtual const Model<parameter_size>& getFunctionModel() const { return m_functionModel; };
	virtual const ErrorModel& getErrorModel() const { return m_errorModel; }
	virtual double getMinError() const { return m_minError; }
	virtual long int getMaxIteration() const { return m_maxIteration; }
	virtual void provideRefData(const Data& ref_data) { (*m_ref_data) = ref_data; }

protected:
	AdditionalParameters m_add_params{};
	Model<parameter_size> m_functionModel;
	ErrorModel m_errorModel;
	std::unique_ptr<Data> m_ref_data{ nullptr };
	long int m_maxIteration{};
	double m_minError{};
	//QUESTION why we don't initialize maxIteration and min error? for example 1000 steps and 0.1 error could be 
	// a good idea. and we might use a roll builderPattern 
};

}

}