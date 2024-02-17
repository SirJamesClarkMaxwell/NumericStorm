#pragma once
#include <array>
#include <iostream>
#include <stdexcept>

#include "Data.hpp"
#include "Model.hpp"
#include "ErrorModel.hpp"
#include "AdditionalParameters.hpp"

namespace NumericStorm {
namespace Fitting {

template <size_t parameter_size>
class Parameters {
public:
    Parameters() {};
    Parameters(std::array<double, parameter_size> parameters)
        : m_parameters(parameters), m_error(-1)
        /*, m_ModelSet(false), m_ErrorModelSet(false), m_errorModel(nullptr), m_model(nullptr)*/ {};


    std::array<double, parameter_size> getParameters();

    double getError();
    double& operator[](int index) 
    {
        return (index >= 0 && static_cast<std::size_t>(index) < parameter_size) ? m_parameters[index] : m_parameters[0];
    }
    const double& operator[](int index) const 
    {
        return (index >= 0 && static_cast<std::size_t>(index) < parameter_size) ? m_parameters[index] : m_parameters[0];
    }
protected:
    std::array<double, parameter_size> m_parameters;
    double m_error;
};

}
}


