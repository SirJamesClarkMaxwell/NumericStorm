#pragma once

#include "Data.hpp"
#include <functional>
#include <memory>

namespace NumericStorm {
namespace Fitting {

class ErrorModel {

public:
    ErrorModel(std::function<double(const std::shared_ptr<Data>&, const std::shared_ptr<Data>&)> errorModel)
        : m_errorModel(errorModel) {}
    ErrorModel(const ErrorModel& other) = default;
    virtual ~ErrorModel() {};
    double operator()(const std::shared_ptr<Data>& referencedData, const std::shared_ptr<Data>& comparedData) const {
        return m_errorModel(referencedData, comparedData);
    };

protected:
    std::function<double(const std::shared_ptr<Data>& referencedData, const std::shared_ptr<Data>& comparedData)> m_errorModel;
};


}
}
