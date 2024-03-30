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
//when I proposed making only functions templated I completely forgot that we have a member field
//that stores the function pointer
//This means that the dimension parameter has to be supplied to that field and thus we cant avoid having 
//templated Model and ErrorModel
template <size_t parameter_size, size_t dimension, class AuxilaryParameters = AdditionalParameters>
class Model
{
public:
    using ModelFunctionType = std::function<void(Data<dimension>&, const Parameters<parameter_size>&, const AuxilaryParameters&)>;
    Model() = delete;
    Model(const ModelFunctionType& model)
        : m_model{ model } {};

    Model(const Model<parameter_size, dimension, AuxilaryParameters>&) = default;
    Model(Model<parameter_size, dimension, AuxilaryParameters>&&) = default;
    Model<parameter_size, dimension, AuxilaryParameters>& operator=(const Model<parameter_size, dimension, AuxilaryParameters>&) = default;
    Model<parameter_size, dimension, AuxilaryParameters>& operator=(Model<parameter_size, dimension, AuxilaryParameters>&&) = default;
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
