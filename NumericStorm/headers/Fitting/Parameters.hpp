#pragma once
#include <array>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "macros.h"

namespace NumericStorm::Fitting {
template <size_t parameter_size>
    class Parameters {
    private:
        using array_t = std::array<double, parameter_size>;
        using array_iter = array_t::iterator;
        using const_array_iter = array_t::const_iterator;

        array_t m_parameters;
    public:
        Parameters() = default;

        Parameters(const std::array<double, parameter_size>& parameters)
            : m_parameters{ parameters }
        {
        }

        virtual ~Parameters() = default;

        const array_t &getParameters() const { return m_parameters; };
        array_t &getParameters() { return m_parameters; };

        virtual constexpr JFM_INLINE
        double& operator[](size_t index) { return m_parameters.at(index); }

        virtual constexpr JFM_INLINE
        const double& operator[](size_t index) const { return m_parameters.at(index); }

        constexpr JFM_INLINE array_iter begin() { return m_parameters.begin(); }
        constexpr JFM_INLINE array_iter end() { return m_parameters.end(); }
        constexpr JFM_INLINE const_array_iter begin() const { return m_parameters.begin(); }
        constexpr JFM_INLINE const_array_iter end() const { return m_parameters.end(); }
        constexpr JFM_INLINE const_array_iter cbegin() const { return m_parameters.cbegin(); }
        constexpr JFM_INLINE const_array_iter cend() const { return m_parameters.cend(); }
    };
}
