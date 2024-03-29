#pragma once

#include "Model.hpp"
#include "ErrorModel.hpp"
#include <memory>
#include <functional>

namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size, class AuxilaryParameters = AdditionalParameters, size_t dimension>
class FitterSettings
{
public:
	FitterSettings(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel, const AuxilaryParameters& add_params, long int maxIteration, double minError)
		: m_functionModel{ model }, m_errorModel{ errorModel }, m_maxIteration{ maxIteration }, m_minError{ minError }, m_add_params{ add_params } {}
	FitterSettings() = delete;
	FitterSettings(const FitterSettings<parameter_size, AdditionalParameters, dimension>&) = default;
	FitterSettings(FitterSettings<parameter_size, AdditionalParameters, dimension>&&) = default;
	FitterSettings<parameter_size, AuxilaryParameters, dimension>& operator=(const FitterSettings<parameter_size, AuxilaryParameters, dimension>&) = default;
	FitterSettings<parameter_size, AuxilaryParameters, dimension>& operator=(FitterSettings<parameter_size, AuxilaryParameters, dimension>&&) = default;

	virtual ~FitterSettings() = default;

	//there is no reason for this to be an abstract class since all the methods return data defined in this very class
	virtual const Model<parameter_size, AuxilaryParameters>& getFunctionModel() const { return m_functionModel; };
	virtual const ErrorModel& getErrorModel() const { return m_errorModel; }
	virtual double getMinError() const { return m_minError; }
	virtual long int getMaxIteration() const { return m_maxIteration; }
	//todo implement builderPattern 
protected:
	AuxilaryParameters m_add_params{};
	Model<parameter_size, AuxilaryParameters> m_functionModel;
	ErrorModel m_errorModel;
	std::unique_ptr<Data<dimension>> m_ref_data{ nullptr };
	long int m_maxIteration{ 1000 };
	double m_minError{ 0.1 };
};
}

}