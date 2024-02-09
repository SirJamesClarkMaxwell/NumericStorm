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
    Model() = default;
    virtual ~Model() = 0;
    virtual Data& operator()(const Parameters<parameter_size>& parameters,
        const AdditionalParameters& additionalParameters) = 0;

protected:
    std::function<Data& (const Parameters<parameter_size>& parameters,
        const AdditionalParameters& additionalParameters)> m_model;
};
}
}
