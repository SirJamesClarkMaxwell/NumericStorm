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
    //we dont want to create a Model with no model
    Model() = delete;
    Model(std::function<Data(const std::vector<double>&, const Parameters<parameter_size>&,
        const AdditionalParameters&)>
        model)
        : m_model{ model } {};

	Model(const Model<parameter_size>&) = default;
    Model(Model<parameter_size>&&) = default;
    Model<parameter_size>& operator=(const Model<parameter_size>&) = default;
    Model<parameter_size>& operator=(Model<parameter_size>&&) = default;
    virtual ~Model() = default;

    virtual Data operator()(const std::vector<double>& arguments, const Parameters<parameter_size>& parameters,
        const AdditionalParameters& additionalParameters) const {
        return m_model(arguments, parameters, additionalParameters);
    }

protected:
    std::function<Data(const std::vector<double>&, const Parameters<parameter_size>&,
        const AdditionalParameters&)> m_model;
};

}
}
