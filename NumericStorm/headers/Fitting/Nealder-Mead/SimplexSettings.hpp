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
	virtual ~SimplexSettings() = default;

public:
	template<class SettingsType>
	using CreatorInfoVector = typename std::vector<CreatorSetUpInfo<SettingsType>>;

	CreatorInfoVector<SimplexCreatorSettings> m_simplexCreatorSetUpInfo;
	CreatorInfoVector<SimplexOperationSettings> m_simplexOperationSetUpInfo;
	CreatorInfoVector<StrategySettings> m_simplexStrategySetUpInfo;


protected:
	template<class BuildingType, class Settings>
	using BaseType = typename FitterSettings<parameter_size, AuxilaryParameters>::FitterSettingsBuilderBase<BuildingType, Settings>;

	template<class BuildingType, class Settings>
	class SimplexSettingsBuilderBase : public FitterSettings<parameter_size, AuxilaryParameters>::FitterSettingsBuilderBase<BuildingType, Settings> {
		static_assert(std::derived_from<Settings, FitterSettings<parameter_size, AuxilaryParameters>> == true);
	public:
		SimplexSettingsBuilderBase() = delete;
		SimplexSettingsBuilderBase(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			BaseType<BuildingType, Settings>{ model, errorModel } {}

		BuildingType& addOperationSettings(const CreatorSetUpInfo<SimplexOperationSettings>& settings)
		{
			this->m_settingsObject.m_simplexOperationSetUpInfo.push_back(settings);
			return this->returnSelf();
		}
		BuildingType& addCreatorSettings(const CreatorSetUpInfo<SimplexCreatorSettings>& settings)
		{
			this->m_settingsObject.m_simplexCreatorSetUpInfo.push_back(settings);
			return this->returnSelf();
		}
		BuildingType& addStrategySettings(const CreatorSetUpInfo<StrategySettings>& settings)
		{
			this->m_settingsObject.m_simplexStrategySetUpInfo.push_back(settings);
			return this->returnSelf();
		}
	};
	/*
	public:

		class SimplexSettingsBuilder : public SimplexSettingsBuilderBase<SimplexSettingsBuilder, SimplexSettings<parameter_size, AuxilaryParameters>> {
		public:
			SimplexSettingsBuilder() = delete;
			SimplexSettingsBuilder(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
				SimplexSettingsBuilderBase<SimplexSettingsBuilder, SimplexSettings<parameter_size, AuxilaryParameters>>{ model, errorModel } {}
		};

		friend class SimplexSettingsBuilderBase<SimplexSettingsBuilder, SimplexSettings<parameter_size, AuxilaryParameters>>;
	*/
};
}