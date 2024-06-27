#pragma once

//#include <ranges>
#include "SimplexSettings.hpp"
#include "Model.hpp"
#include "ErrorModel.hpp"
#include "SimplexOperationsHeader.hpp"
//todo we need to discus bout how we gonna implement the actual basic fitter


namespace NumericStorm::Fitting
{
template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class BasicSimplexOptimizerSettings : public SimplexSettings<parameter_size, AuxilaryParameters>
{
public:

	explicit BasicSimplexOptimizerSettings(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel)
		: SimplexSettings<parameter_size>{ model, errorModel } {}
	virtual ~BasicSimplexOptimizerSettings() = default;


protected:
	template<class BuildingType, class Settings>
	using BaseType = typename SimplexSettings<parameter_size, AuxilaryParameters>::SimplexSettingsBuilderBase<BuildingType, Settings>;

	template<class BuildingType, class Settings>
	class BasicSimplexSettingsBuilderBase : public SimplexSettings<parameter_size, AuxilaryParameters>::SimplexSettingsBuilderBase<BuildingType, Settings> {
		static_assert(std::derived_from<Settings, OptimizerSettings<parameter_size, AuxilaryParameters>> == true);
	public:
		BasicSimplexSettingsBuilderBase() = delete;
		BasicSimplexSettingsBuilderBase(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			BaseType<BuildingType, Settings>{ model, errorModel } {}

	};

public:

	class BasicSimplexSettingsBuilder : public BasicSimplexSettingsBuilderBase<BasicSimplexSettingsBuilder, BasicSimplexOptimizerSettings<parameter_size, AuxilaryParameters>> {
	public:
		BasicSimplexSettingsBuilder() = delete;
		BasicSimplexSettingsBuilder(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			BasicSimplexSettingsBuilderBase<BasicSimplexSettingsBuilder, BasicSimplexOptimizerSettings<parameter_size, AuxilaryParameters>>{ model, errorModel } {}
	};

	friend class BasicSimplexSettingsBuilderBase<BasicSimplexSettingsBuilder, BasicSimplexOptimizerSettings<parameter_size, AuxilaryParameters>>;


};

}






