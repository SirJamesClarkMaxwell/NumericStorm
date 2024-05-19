#pragma once

#include "SimplexSettings.hpp"
#include "Model.hpp"
#include "ErrorModel.hpp"
#include "SimplexOperationsHeader.hpp"
#include <ranges>
//todo we need to discus bout how we gonna implement the actual basic fitter


namespace NumericStorm::Fitting
{
template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class BasicSimplexFitterSettings : private SimplexSettings<parameter_size, AuxilaryParameters>
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
	using BaseType = typename SimplexSettings<parameter_size, AuxilaryParameters>::SimplexSettingsBuilderBase;

	template<class B, class Settings>
	class BasicSimplexSettingsBuilderBase : public SimplexSettings<parameter_size, AuxilaryParameters>::SimplexSettingsBuilderBase<B, Settings> {
	public:
		BasicSimplexSettingsBuilderBase() = delete;
		BasicSimplexSettingsBuilderBase(const Model<parameter_size, AuxilaryParameters>& model, const ErrorModel& errorModel) :
			BaseType{ model, errorModel } {}


		virtual B& minParameters(const Parameters<parameter_size>& bounds) {
			parametersMinBounds = bounds;
			return this->returnSelf();
		}

		virtual B& maxParameters(const Parameters<parameter_size>& bounds) {
			parametersMaxBounds = bounds;
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






