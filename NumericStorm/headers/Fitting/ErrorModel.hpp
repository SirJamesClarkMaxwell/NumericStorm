#pragma once

#include "Data.hpp"
#include <functional>

namespace NumericStorm {
namespace Fitting {


class ErrorModel {

public:
    ErrorModel() = delete;
    ErrorModel(const ErrorModel&) = default;
    ErrorModel(ErrorModel&&) = default;
    ErrorModel& operator=(const ErrorModel&) = default;
    ErrorModel& operator=(ErrorModel&&) = default;


    ErrorModel(std::function<double(const Data&, const Data&)> errorModel)
        : m_errorModel{ errorModel } {}

    virtual ~ErrorModel() {};
    virtual double operator()(const Data& referencedData, const Data& comparedData) const {
        return m_errorModel(referencedData, comparedData);
    }

protected:
    std::function<double(const Data&, const Data&)> m_errorModel;
};
}
}
