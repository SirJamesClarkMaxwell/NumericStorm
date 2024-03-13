#pragma once
#include <memory>

#include "../FitterSettings.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size>
class SimplexSettings : public FitterSettings<parameter_size>
{
	SimplexSettings() = delete;
	SimplexSettings(const SimplexSettings<parameter_size>&) = default;
	SimplexSettings(SimplexSettings<parameter_size>&&) = default;
	SimplexSettings<parameter_size>& operator=(const SimplexSettings<parameter_size>&) = default;
	SimplexSettings<parameter_size>& operator=(SimplexSettings<parameter_size>&&) = default;

	virtual ~SimplexSettings() = default;

	SimplexSettings(const Model<parameter_size>& model, const ErrorModel& errorModel, int maxIteration, double minError)
		: FitterSettings<parameter_size>(model, errorModel, maxIteration, minError) {}
};
}
}