#pragma once
#include <array>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "Model.hpp"
#include "ErrorModel.hpp"
#include "AdditionalParameters.hpp"

namespace NumericStorm {
namespace Fitting {



template <size_t parameter_size>
class Parameters {
public:
    Parameters(const std::array<double, parameter_size>& parameters)
        : m_parameters{ parameters } {}
    Parameters(std::initializer_list<double>& parameters)
        :m_parameters{ checkBoundsOfParameters(parameters) and parameters } {};
    Parameters() = default;
    Parameters(const Parameters<parameter_size>&) = default;
    Parameters(Parameters<parameter_size>&&) = default;
    Parameters<parameter_size>& operator=(const Parameters<parameter_size>&) = default;
    Parameters<parameter_size>& operator=(Parameters<parameter_size>&&) = default;

    virtual ~Parameters() = default;
    virtual const std::array<double, parameter_size>& getParameters() const { return m_parameters; };

    virtual double& operator[](int index)
    {
        if (index > parameter_size - 1 || index < 0)
            throw std::out_of_range("Index out of bounds");
        return m_parameters[index];
    }
    virtual const double& operator[](int index) const
    {
        if (index > parameter_size - 1 || index < 0)
            throw std::out_of_range("Index out of bounds");
        return m_parameters[index];
    }
private:
    std::array<double, parameter_size> m_parameters{};
    bool checkBoundsOfParameters(const std::initializer_list<double>& parameters) const
    {
        if (parameters.size() != parameter_size)
            throw std::out_of_range("Initializer list size does not match parameter size");
        return true;
    };
};
}
}



