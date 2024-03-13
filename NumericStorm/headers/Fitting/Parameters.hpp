#pragma once
#include <array>
#include <iostream>
#include <stdexcept>

#include "Model.hpp"
#include "ErrorModel.hpp"
#include "AdditionalParameters.hpp"
//TODO: add unpack method that will return a tuple of parameters -> this will provide us to use structure binding

namespace NumericStorm {
namespace Fitting {



template <size_t parameter_size>
class Parameters {
public:
    //instead of default constructor we initialize members by default
    Parameters() = default;
    Parameters(const Parameters<parameter_size>&) = default;
    Parameters(Parameters<parameter_size>&&) = default;
    Parameters<parameter_size>& operator=(const Parameters<parameter_size>&) = default;
    Parameters<parameter_size>& operator=(Parameters<parameter_size>&&) = default;

    virtual ~Parameters() = default;

    Parameters(const std::array<double, parameter_size>& parameters)
        : m_parameters{ parameters }, m_error{ -1 } {}

    virtual const std::array<double, parameter_size>& getParameters() const { return m_parameters; }
    virtual double getError() const { return m_error; }
    virtual bool isErrorValid() const { return m_error_valid; }
    virtual void updateError(double error) { m_error = error; m_error_valid = true; }

    virtual double& operator[](int index) noexcept
    {
        //error invalidation since parameters were modified
        m_error_valid = false;

        //we dont expect someone to create parameters with 0 elements so if someone does - its their problem
        //for now - might change later
        if (index >= 0 && static_cast<std::size_t>(index) < parameter_size)
            return m_parameters[index];
        return m_parameters[0];
    }
    virtual const double& operator[](int index) const noexcept
    {
        if (index >= 0 && static_cast<std::size_t>(index) < parameter_size)
            return m_parameters[index];
        return m_parameters[0];
    }
protected:
    //since error is calculated outside the Parameters it might be presented incorrectly at some point in time inside an instance
    //if the parameter values were updated but the error not changed 
    bool m_error_valid{ false };
    std::array<double, parameter_size> m_parameters{};
    double m_error{-1};
};
}
}



