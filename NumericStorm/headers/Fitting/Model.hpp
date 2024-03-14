#pragma once

#include <functional>
#include "AdditionalParameters.hpp"
#include "Data.hpp"
#include "Parameters.hpp"

namespace NumericStorm
{
namespace Fitting
{

template <size_t parameter_size>
class Model
{
public:
	Model(std::function<std::unique_ptr<Data>(const std::vector<double>& arguments, const Parameters<parameter_size>& parameters,
		const AdditionalParameters& additionalParameters)>
		model)
		: m_model(model) {};
	Model(const Model<parameter_size>& other) = default;
	virtual ~Model() {};
	std::shared_ptr<Data> operator()(const std::vector<double>& arguments, const Parameters<parameter_size>& parameters,
		const AdditionalParameters& additionalParameters);

protected:
	std::function<std::unique_ptr<Data>(const std::vector<double>& arguments, const Parameters<parameter_size>& parameters,
		const AdditionalParameters& additionalParameters)> m_model;
};

template <size_t parameter_size>
std::shared_ptr<Data> Model<parameter_size>::operator()(const std::vector<double>& arguments, const Parameters<parameter_size>& parameters, const AdditionalParameters& additionalParameters)
{
	return std::move(m_model(arguments, parameters, additionalParameters));
}
}
}
