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
class BasicSimplexFitterSettings : public SimplexSettings<parameter_size, AuxilaryParameters>
{
public:

	explicit BasicSimplexFitterSettings(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel)
		: SimplexSettings<parameter_size>{ model, errorModel } {}

	/*
	BasicSimplexFitterSettings(const BasicSimplexFitterSettings<parameter_size>&) = default;
	BasicSimplexFitterSettings(BasicSimplexFitterSettings<parameter_size>&&) = default;
	BasicSimplexFitterSettings<parameter_size>& operator=(const BasicSimplexFitterSettings<parameter_size>&) = default;
	BasicSimplexFitterSettings<parameter_size>& operator=(BasicSimplexFitterSettings<parameter_size>&&) = default;
	*/

	virtual ~BasicSimplexFitterSettings() = default;
public:
	Parameters<parameter_size> parametersMinBounds{  };
	Parameters<parameter_size> parametersMaxBounds{  };


protected:
	template<class B, class Settings>
	using BaseType = typename SimplexSettings<parameter_size, AuxilaryParameters>::SimplexSettingsBuilderBase<B, Settings>;

	template<class B, class Settings>
	class BasicSimplexSettingsBuilderBase : public SimplexSettings<parameter_size, AuxilaryParameters>::SimplexSettingsBuilderBase<B, Settings> {
		static_assert(std::derived_from<Settings, FitterSettings<parameter_size, AuxilaryParameters>> == true);
	public:
		BasicSimplexSettingsBuilderBase() = delete;
		BasicSimplexSettingsBuilderBase(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			BaseType<B, Settings>{ model, errorModel } {}


		virtual B& minParameters(const Parameters<parameter_size>& bounds) {
			this->m_settingsObject.parametersMinBounds = bounds;
			return this->returnSelf();
		}

		virtual B& maxParameters(const Parameters<parameter_size>& bounds) {
			this->m_settingsObject.parametersMaxBounds = bounds;
			return this->returnSelf();
		}
	};

public:

	class BasicSimplexSettingsBuilder : public BasicSimplexSettingsBuilderBase<BasicSimplexSettingsBuilder, BasicSimplexFitterSettings<parameter_size, AuxilaryParameters>> {
	public:
		BasicSimplexSettingsBuilder() = delete;
		BasicSimplexSettingsBuilder(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			BasicSimplexSettingsBuilderBase<BasicSimplexSettingsBuilder, BasicSimplexFitterSettings<parameter_size, AuxilaryParameters>>{ model, errorModel } {}
	};

	friend class BasicSimplexSettingsBuilderBase<BasicSimplexSettingsBuilder, BasicSimplexFitterSettings<parameter_size, AuxilaryParameters>>;


};

}






