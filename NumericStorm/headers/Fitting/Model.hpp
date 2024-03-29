#pragma once

#include <functional>
#include "AdditionalParameters.hpp"
#include "Data.hpp"
#include "Parameters.hpp"

#include <memory>

namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class Model
{
public:
    template <size_t dimension>
    using ModelFunctionType = std::function<void(Data<dimension>&, const Parameters<parameter_size>&, const AuxilaryParameters&)>;
    Model() = delete;
    Model(const ModelFunctionType& model)
        : m_model{ model } {};

    Model(const Model<parameter_size, AuxilaryParameters>&) = default;
    Model(Model<parameter_size, AuxilaryParameters>&&) = default;
    Model<parameter_size, AuxilaryParameters>& operator=(const Model<parameter_size, AuxilaryParameters>&) = default;
    Model<parameter_size, AuxilaryParameters>& operator=(Model<parameter_size, AuxilaryParameters>&&) = default;
    virtual ~Model() = default;

    virtual void operator()(Data<dimension>& arguments, const Parameters<parameter_size>& parameters, const AuxilaryParameters& additionalParameters) const
    {
        m_model(arguments, parameters, additionalParameters);
    }
protected:
    ModelFunctionType m_model;
};

}
}
