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
class OptimizerSettings
{
public:
	OptimizerSettings(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel)
		: m_functionModel{ model }, m_errorModel{ errorModel } {}
	OptimizerSettings() = delete;

	virtual ~OptimizerSettings() = default;

	virtual const Model<parameter_size, AuxilaryParameters>& getFunctionModel() const { return m_functionModel; };
	virtual const ErrorModel& getErrorModel() const { return m_errorModel; }
	virtual double getMinError() const { return m_minError; }
	virtual long int getMaxIteration() const { return m_maxIteration; }
	virtual std::shared_ptr<Data> getReferencedData()	const { return m_ref_data; }
	//todo implement builderPattern 
	friend class OptimizerSettingsBuilderBase;
private:
	Model<parameter_size, AuxilaryParameters> m_functionModel;
	ErrorModel m_errorModel;

	std::shared_ptr<Data> m_ref_data{ nullptr };
	long int m_maxIteration{ 1000 };
	double m_minError{ 0.1 };
	bool m_useBounds{ false };
	Parameters<parameter_size> parametersMinBounds{  };
	Parameters<parameter_size> parametersMaxBounds{  };

protected:

	template<class BuildingType, class Settings>
	class OptimizerSettingsBuilderBase {
		static_assert(std::derived_from<Settings, OptimizerSettings<parameter_size, AuxilaryParameters>> == true);
	public:
		OptimizerSettingsBuilderBase() = delete;
		OptimizerSettingsBuilderBase(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			m_settingsObject{ model, errorModel } {}

		Settings build() { return m_settingsObject; }
		BuildingType& returnSelf() { return static_cast<BuildingType&>(*this); }

		BuildingType& maxIteration(long int iterations)
		{
			this->m_settingsObject.m_maxIteration = iterations;
			return returnSelf();
		}
		BuildingType& minError(double error)
		{
			this->m_settingsObject.m_minError = error;
			return returnSelf();
		}
		BuildingType& useBounds(bool useBounds)
		{
			this->m_settingsObject.m_useBounds = useBounds;
			return returnSelf();
		}
		BuildingType& refData(const std::shared_ptr<Data>& data)
		{
			this->m_settingsObject.m_ref_data = data;
			return returnSelf();
		}
		BuildingType& minParameters(const Parameters<parameter_size>& bounds)
		{
			this->m_settingsObject.parametersMinBounds = bounds;
			return returnSelf();
		}
		BuildingType& maxParameters(const Parameters<parameter_size>& bounds)
		{
			this->m_settingsObject.parametersMaxBounds = bounds;
			return returnSelf();
		}
	protected:
		Settings m_settingsObject;
	};
	/*


	public:
		class FitterSettingsBuilder : public FitterSettingsBuilderBase<FitterSettingsBuilder, FitterSettings<parameter_size, AuxilaryParameters>> {
		public:
			FitterSettingsBuilder() = delete;
			FitterSettingsBuilder(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
				FitterSettingsBuilderBase<FitterSettingsBuilder, FitterSettings<parameter_size, AuxilaryParameters>>{ model, errorModel } {}
		};

		friend class FitterSettingsBuilderBase<FitterSettingsBuilder, FitterSettings<parameter_size, AuxilaryParameters>>;
	*/
};
}
