#pragma once
#include <array>
#include <iostream>
#include <stdexcept>
#include "Fitting.hpp"

namespace NumericStorm {
namespace Fitting {

template <size_t size_p>
class Parameters {
public:
    Parameters<size_p>() = default;
    Parameters<size_p>(std::array<double, size_p> parameters)
        : m_parameters(parameters), m_error(0.0), m_ModelSet(false), m_ErrorModelSet(false), m_errorModel(nullptr), m_model(nullptr) {};

    virtual double& operator [](int index) = 0;
    virtual std::array<double, size_p> getParameters() = 0;

    virtual double getError() = 0;
    virtual void setUp() = 0;

    virtual void calculateError(const Data* referenceData) = 0;

protected:
    std::array<double, size_p> m_parameters;
    double m_error;
    AdditionalParameters m_additionalParameters;
    Model<size_p>* m_model;
    ErrorModel* m_errorModel;
    bool m_ModelSet;
    bool m_ErrorModelSet;

protected:
    void setModel(const Model<size_p>* modelToSet) 
    {
        m_model = modelToSet;
        m_ModelSet = true;
    };
    void setErrorModel(const ErrorModel* errorModelToSet)
    {
        m_errorModel = errorModelToSet;
        m_ErrorModelSet = true;
    };
};
}
}
