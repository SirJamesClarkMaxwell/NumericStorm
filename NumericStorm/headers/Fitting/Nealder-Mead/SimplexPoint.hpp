#pragma once
#include "../Parameters.hpp"
#include <concepts>
#include <type_traits>

namespace NumericStorm 
{
namespace Fitting 
{


    template <std::size_t parameter_size>
    class SimplexPoint : public Parameters<parameter_size> {
    public:
        using Parameters<parameter_size>::m_parameters; 

        SimplexPoint() = default;
        SimplexPoint(std::array<double, parameter_size> parameters)
            : Parameters<parameter_size>(parameters) {};

        // Operator overloads
        double& operator[](int index) {
            return (index >= 0 && static_cast<std::size_t>(index) < parameter_size) ? m_parameters[index] : m_parameters[0];
        }

        const double& operator[](int index) const {
            return (index >= 0 && static_cast<std::size_t>(index) < parameter_size) ? m_parameters[index] : m_parameters[0];
        }

        bool operator==(const Parameters<parameter_size>& other) const { return 
            m_parameters == other.getParameters(); }
        bool operator==(const std::array<double, parameter_size>& other) const {
            return m_parameters == other;
        };
        SimplexPoint<parameter_size>& operator=(const Parameters<parameter_size>& other) {
            if (this != &other)
                m_parameters = other.getParameters();
            return *this;
        }

        SimplexPoint<parameter_size>& operator+=(const Parameters<parameter_size>& other) {
            for (int i = 0; i < parameter_size; ++i)
                m_parameters[i] += other[i];
            return *this;
        }
        SimplexPoint<parameter_size>& operator-=(const Parameters<parameter_size>& other) {
            for (int i = 0; i < parameter_size; ++i)
                m_parameters[i] -= other[i];
            return *this;
        }
        SimplexPoint<parameter_size>& operator*=(const auto& other) {
            for (std::size_t i = 0; i < parameter_size; ++i)
                m_parameters[i] *= other;
            return *this;
        }
        SimplexPoint<parameter_size>& operator/=(const auto& other) {
            for (std::size_t i = 0; i < parameter_size; ++i)
                m_parameters[i] /= other;
            return *this;
        }

        SimplexPoint<parameter_size>& operator+(const Parameters<parameter_size>& other) const {
            SimplexPoint result = *this;
            result += other;
            return result;
        }
        SimplexPoint<parameter_size>& operator-(const Parameters<parameter_size>& other) const {
            SimplexPoint result = *this;
            result -= other;
            return result;
        }
        SimplexPoint<parameter_size>& operator*(const auto& other) const {
            SimplexPoint result = *this;
            result *= other;
            return result;
        }
        SimplexPoint<parameter_size>& operator/(const auto& other) const {
            SimplexPoint result = *this;
            result /= other;
            return result;
        }

    private:
        // Helper functions can be added here if needed
    };



}

}