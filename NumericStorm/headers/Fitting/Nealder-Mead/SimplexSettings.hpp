#pragma once
#include <memory>

#include "../FitterSettings.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class SimplexSettings : public FitterSettings<parameter_size, AuxilaryParameters>
{
	//todo implement builder
	SimplexSettings(const Model<parameter_size>& model, const ErrorModel& errorModel, int maxIteration, double minError)
		: FitterSettings<parameter_size, AuxilaryParameters>(model, errorModel, maxIteration, minError) {}
	SimplexSettings() = delete;
	SimplexSettings(const SimplexSettings<parameter_size, AuxilaryParameters>&) = default;
	SimplexSettings(SimplexSettings<parameter_size, AuxilaryParameters>&&) = default;
	SimplexSettings<parameter_size, AuxilaryParameters>& operator=(const SimplexSettings<parameter_size, AuxilaryParameters>&) = default;
	SimplexSettings<parameter_size, AuxilaryParameters>& operator=(SimplexSettings<parameter_size, AuxilaryParameters>&&) = default;
	virtual ~SimplexSettings() = default;
};
}
}