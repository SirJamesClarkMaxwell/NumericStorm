#pragma once
#include <memory>
#include <functional>

#include "Model.hpp"
#include "ErrorModel.hpp"
#include "Bounds.hpp"
#include "AdditionalParameters.hpp"
namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class FitterSettings
{
public:
	FitterSettings(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel, long int maxIteration, double minError, bool useBounds)
		: m_functionModel{ model }, m_errorModel{ errorModel }, m_maxIteration{ maxIteration }, m_minError{ minError }, m_useBounds(useBounds) {}
	FitterSettings() = delete;
	FitterSettings(const FitterSettings<parameter_size, AuxilaryParameters>&) = default;
	FitterSettings(FitterSettings<parameter_size, AuxilaryParameters>&&) = default;
	FitterSettings<parameter_size, AuxilaryParameters>& operator=(const FitterSettings<parameter_size, AuxilaryParameters>&) = default;
	FitterSettings<parameter_size, AuxilaryParameters>& operator=(FitterSettings<parameter_size, AuxilaryParameters>&&) = default;

	virtual ~FitterSettings() = default;

	virtual const Model<parameter_size, AuxilaryParameters>& getFunctionModel() const { return m_functionModel; };
	virtual const ErrorModel& getErrorModel() const { return m_errorModel; }
	virtual double getMinError() const { return m_minError; }
	virtual long int getMaxIteration() const { return m_maxIteration; }
	//todo implement builderPattern 
protected:
	Model<parameter_size, AuxilaryParameters> m_functionModel;
	ErrorModel m_errorModel;

	std::shared_ptr<const Data> m_ref_data{ nullptr };
	long int m_maxIteration{ 1000 };
	double m_minError{ 0.1 };
	bool m_useBounds{ false };

};
}

}