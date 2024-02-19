#pragma once

#include <functional>
#include "AdditionalParameters.hpp"
#include "Data.hpp"
#include "Parameters.hpp"

namespace NumericStorm {
namespace Fitting {

template <size_t parameter_size>
class Model {
public:
    Model(std::function<std::unique_ptr<Data>(const std::vector<double>& arguments, const Parameters<parameter_size>& parameters,
        const AdditionalParameters& additionalParameters)> model)
        :m_model(model) {};
    virtual ~Model()=0;
    virtual std::unique_ptr<Data> operator()(const std::vector<double>& arguments,const Parameters<parameter_size>& parameters,
        const AdditionalParameters& additionalParameters) = 0;

protected:
    std::function<std::unique_ptr<Data> (const std::vector<double>& arguments,const Parameters<parameter_size>& parameters,
        const AdditionalParameters& additionalParameters)> m_model;
};
template<size_t parameter_size>
Model<parameter_size>::~Model() {};
}
}
