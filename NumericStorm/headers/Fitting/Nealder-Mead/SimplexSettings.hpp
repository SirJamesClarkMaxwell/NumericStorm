#pragma once
#include <memory>

#include "FitterSettings.hpp"
#include "Model.hpp"
#include "ErrorModel.hpp"
#include "Factory.hpp"
#include "SimplexCreatorSettings.hpp"
#include "StrategySettings.hpp"
#include "SimplexOperationSettings.hpp"


namespace NumericStorm::Fitting
{

template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class SimplexSettings : public FitterSettings<parameter_size, AuxilaryParameters>
{

public:
	//todo implement builder
	SimplexSettings(const Model<parameter_size>& model, const ErrorModel& errorModel)
		: FitterSettings<parameter_size, AuxilaryParameters>{ model, errorModel } {}
	SimplexSettings() = delete;
	SimplexSettings(const SimplexSettings<parameter_size, AuxilaryParameters>&) = default;
	SimplexSettings(SimplexSettings<parameter_size, AuxilaryParameters>&&) = default;
	SimplexSettings<parameter_size, AuxilaryParameters>& operator=(const SimplexSettings<parameter_size, AuxilaryParameters>&) = default;
	SimplexSettings<parameter_size, AuxilaryParameters>& operator=(SimplexSettings<parameter_size, AuxilaryParameters>&&) = default;
	virtual ~SimplexSettings() = default;

public:
	template<class SettingsType>
	using CreatorInfoVector = typename std::vector<CreatorSetUpInfo<SettingsType>>;

	CreatorInfoVector<SimplexCreatorSettings> m_simplexCreatorSetUpInfo;
	CreatorInfoVector<SimplexOperationSettings> m_simplexOperationSetUpInfo;
	CreatorInfoVector<StrategySettings> m_simplexStrategySetUpInfo;


protected:
	using BaseType = typename FitterSettings<parameter_size, AuxilaryParameters>::FitterSettingsBuilderBase;

	template<class B, class Settings>
	class SimplexSettingsBuilderBase : public FitterSettings<parameter_size, AuxilaryParameters>::FitterSettingsBuilderBase<B, Settings> {
	public:
		SimplexSettingsBuilderBase() = delete;
		SimplexSettingsBuilderBase(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			BaseType{ model, errorModel } {}


		virtual B& addOperationSettings(const SimplexOperationSettings& settings) {
			this->m_settingsObject.m_simplexOperationSetUpInfo.push_back(settings);
			return this->returnSelf();
		}

		virtual B& addCreatorSettings(const SimplexCreatorSettings& settings) {
			this->m_settingsObject.m_simplexCreatorSetUpInfo.push_back(settings);
			return this->returnSelf();
		}

		virtual B& addStrategySettings(const StrategySettings& settings) {
			this->m_settingsObject.m_simplexStrategySetUpInfo.push_back(settings);
			return this->returnSelf();
		}
	};

public:

	class SimplexSettingsBuilder : public SimplexSettingsBuilderBase<SimplexSettingsBuilder, SimplexSettings<parameter_size, AuxilaryParameters>> {
	public:
		SimplexSettingsBuilder() = delete;
		SimplexSettingsBuilder(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			SimplexSettingsBuilderBase<SimplexSettingsBuilder, SimplexSettings<parameter_size, AuxilaryParameters>>{ model, errorModel } {}
	};

	friend class SimplexSettingsBuilderBase<SimplexSettingsBuilder, SimplexSettings<parameter_size, AuxilaryParameters>>;
};
}