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
    class Model;

template <size_t parameter_size>
class Parameters {
public:
    //Parameters() = default;
    Parameters(std::array<double, parameter_size> parameters)
        : m_parameters(parameters), m_error(-1), m_ModelSet(false), m_ErrorModelSet(false), m_errorModel(nullptr), m_model(nullptr) {};

    virtual double& operator [](int index) = 0;
    virtual std::array<double, parameter_size> getParameters() = 0;

    virtual double getError() = 0;
    virtual void setUp() = 0;

    virtual void calculateError(const Data* referenceData) = 0;

protected:
    std::array<double, parameter_size> m_parameters;
    double m_error;
    AdditionalParameters m_additionalParameters;
    std::unique_ptr<Model<parameter_size>> m_model;
    ErrorModel* m_errorModel;
    bool m_ModelSet;
    bool m_ErrorModelSet;

protected:
    void setModel(Model<parameter_size>* modelToSet) 
    {
        m_model = modelToSet;
        m_ModelSet = true;
    };
    void setErrorModel(ErrorModel* errorModelToSet)
    {
        m_errorModel = errorModelToSet;
        m_ErrorModelSet = true;
    };
};
}
}
