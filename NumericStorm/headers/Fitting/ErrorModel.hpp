#pragma once

#include "Data.hpp"
#include <functional>

namespace NumericStorm {
namespace Fitting {

template <size_t dimension>
class ErrorModel {

public:
    ErrorModel() = delete;
    ErrorModel(const ErrorModel<dimension>&) = default;
    ErrorModel(ErrorModel<dimension>&&) = default;
    ErrorModel<dimension>& operator=(const ErrorModel<dimension>&) = default;
    ErrorModel<dimension>& operator=(ErrorModel<dimension>&&) = default;


    ErrorModel(std::function<double(const Data<dimension>&, const Data<dimension>&)> errorModel)
        : m_errorModel{ errorModel } {}

    virtual ~ErrorModel() {};
    virtual double operator()(const Data<dimension>& referencedData, const Data<dimension>& comparedData) const {
        return m_errorModel(referencedData, comparedData);
    }

protected:
    std::function<double(const Data<dimension>&, const Data<dimension>&)> m_errorModel;
};
}
}
