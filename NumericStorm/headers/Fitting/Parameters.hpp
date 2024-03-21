#pragma once
#include <array>
#include <iostream>
#include <stdexcept>

#include "Data.hpp"
#include "Model.hpp"
#include "ErrorModel.hpp"
#include "AdditionalParameters.hpp"
//TODO: add unpack method that will return a tuple of parameters -> this will provide us to use structure binding

namespace NumericStorm {
namespace Fitting {



template <size_t parameter_size>
class Parameters {
public:
    Parameters() { m_parameters.fill(0); };
    Parameters(std::array<double, parameter_size> parameters)
        : m_parameters(parameters) {}
    std::array<double, parameter_size> getParameters() { return m_parameters; }
    double& operator[](int index) noexcept
    {
        if (index >= 0 && static_cast<std::size_t>(index) < parameter_size)
            return m_parameters[index];
        return m_parameters[0];
    }
    const double& operator[](int index) const noexcept
    {
        if (index >= 0 && static_cast<std::size_t>(index) < parameter_size)
            return m_parameters[index];
        return m_parameters[0];
    }
protected:
    std::array<double, parameter_size> m_parameters;

};
}
}



