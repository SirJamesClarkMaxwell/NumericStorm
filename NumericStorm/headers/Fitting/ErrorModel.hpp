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


    ErrorModel(std::function<double(const Data&, const Data&)> errorModel, bool revert = false)
        : m_errorModel{ errorModel }, m_revert{ revert } {}

    virtual ~ErrorModel() {};
    virtual double operator()(const Data& referencedData, const Data& comparedData) const {
        double error = m_errorModel(referencedData, comparedData);

        return  !m_revert ? error : 1 / error;
    }

protected:
    std::function<double(const Data&, const Data&)> m_errorModel;
    bool m_revert{ false };
};
}
}
