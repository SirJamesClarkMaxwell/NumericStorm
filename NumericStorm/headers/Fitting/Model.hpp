#pragma once

#include <functional>
#include "AdditionalParameters.hpp"
#include "Data.hpp"
#include "Parameters.hpp"

namespace NumericStorm {
namespace Fitting {

template <size_t size_p>
class Model {
public:
    Model() = default;
    virtual ~Model() {};
    virtual Data& operator()(const Parameters<size_p>& parameters,
        const AdditionalParameters& additionalParameters) = 0;

protected:
    std::function<Data& (const Parameters<size_p>& parameters,
        const AdditionalParameters& additionalParameters)> m_model;
};
}
}
