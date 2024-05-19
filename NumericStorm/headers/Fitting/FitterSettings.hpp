#pragma once
#include <memory>
#include <functional>

#include "Model.hpp"
#include "ErrorModel.hpp"
#include "Bounds.hpp"
#include "AdditionalParameters.hpp"
#include "Data.hpp"


namespace NumericStorm::Fitting
{
template <size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class FitterSettings
{
public:
	FitterSettings(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel)
		: m_functionModel{ model }, m_errorModel{ errorModel } {}
	FitterSettings() = delete;

	virtual ~FitterSettings() = default;

	virtual const Model<parameter_size, AuxilaryParameters>& getFunctionModel() const { return m_functionModel; };
	virtual const ErrorModel& getErrorModel() const { return m_errorModel; }
	virtual double getMinError() const { return m_minError; }
	virtual long int getMaxIteration() const { return m_maxIteration; }
	virtual std::shared_ptr<const Data> getReferencedData()	const { return m_ref_data; }
	//todo implement builderPattern 
public:
	Model<parameter_size, AuxilaryParameters> m_functionModel;
	ErrorModel m_errorModel;

	std::shared_ptr<const Data> m_ref_data{ nullptr };
	long int m_maxIteration{ 1000 };
	double m_minError{ 0.1 };
	bool m_useBounds{ false };

protected:


	template<class B, class Settings>
	class FitterSettingsBuilderBase {
		static_assert(std::derived_from<Settings, FitterSettings<parameter_size, AuxilaryParameters>> == true);
	public:
		FitterSettingsBuilderBase() = delete;
		FitterSettingsBuilderBase(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			m_settingsObject{ model, errorModel } {}

		virtual B& returnSelf() { return *this; }

		virtual B& maxIteration(long int iterations) {
			m_settingsObject.m_maxIteration = iterations;
			return returnSelf();
		}

		virtual B& minError(double error) {
			m_settingsObject.m_minError = error;
			return returnSelf();
		}

		virtual B& useBounds(bool useBounds) {
			m_settingsObject.m_useBounds = useBounds;
			return returnSelf();
		}

		virtual Settings build() { return m_settingsObject; }

	protected:
		Settings m_settingsObject;
	};



public:
	class FitterSettingsBuilder : public FitterSettingsBuilderBase<FitterSettingsBuilder, FitterSettings<parameter_size, AuxilaryParameters>> {
	public:
		FitterSettingsBuilder() = delete;
		FitterSettingsBuilder(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			FitterSettingsBuilderBase<FitterSettingsBuilder, FitterSettings<parameter_size, AuxilaryParameters>>{ model, errorModel } {}
	};

	friend class FitterSettingsBuilderBase<FitterSettingsBuilder, FitterSettings<parameter_size, AuxilaryParameters>>;
};
}
