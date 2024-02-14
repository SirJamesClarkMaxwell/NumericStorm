#pragma once
#include "../Parameters.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"

#include <concepts>
#include <type_traits>
#include <memory>


namespace NumericStorm 
{
namespace Fitting 
{


template <std::size_t parameter_size>
class SimplexPoint : {
public:

		SimplexPoint() = default;
		SimplexPoint(std::array<double, parameter_size> parameters)
			: m_parameters(parameters),m_error(-1) {};
		std::array<double, parameter_size> getParameters() 
			{ return m_parameters.getParameters();}

		// Operator overloads
		double& operator[](int index) {
			return (index >= 0 && static_cast<std::size_t>(index) < parameter_size) ? m_parameters[index] : m_parameters[0];
		}

		const double& operator[](int index) const {
			return (index >= 0 && static_cast<std::size_t>(index) < parameter_size) ? m_parameters[index] : m_parameters[0];
		}

		bool operator ==(const SimplexPoint<parameter_size>& other) const 
			{ return m_parameters.getParameters() == other.getParameters(); }
		bool operator == (const std::array<double, parameter_size>& other) const 
			{return m_parameters.getParameters() == other;};
		bool operator <=> (const SimplexPoint<parameter_size>& other) const 
			{return m_error <=> other.m_error;}
		SimplexPoint<parameter_size>& operator=(const SimplexPoint<parameter_size>& other) {
			if (this != &other)
			{
				m_parameters = other.getParameters();
				m_error = other.m_error;
			}
				
			return *this;
		}

		SimplexPoint<parameter_size>& operator+=(const SimplexPoint<parameter_size>& other) {
			for (int i = 0; i < parameter_size; ++i)
				m_parameters[i] += other[i];
			return *this;
		}
		SimplexPoint<parameter_size>& operator-=(const SimplexPoint<parameter_size>& other) {
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

		SimplexPoint<parameter_size> operator+(const SimplexPoint<parameter_size>& other) const {
			SimplexPoint result = *this;
			result += other;
			return result;
		}
		SimplexPoint<parameter_size> operator-(const SimplexPoint<parameter_size>& other) const {
			SimplexPoint result = *this;
			result -= other;
			return result;
		}
		SimplexPoint<parameter_size> operator*(const auto& other) const {
			SimplexPoint result = *this;
			result *= other;
			return result;
		}
		SimplexPoint<parameter_size> operator/(const auto& other) const {
			SimplexPoint result = *this;
			result /= other;
			return result;
		}
	private:
		Parameters<parameters_size> m_parameters;
		double m_error;
		bool m_modelSet;
		bool m_errorModelSet;
		std::unique_ptr<Model> m_model;
		std::unique_ptr<ErrorModel> m_errorModel;
		//TODO add functions to setting model
		//TODO add functions to setting error model
		//TODO initialize bools as false
		//TODO add setUp function
		//TODO add function to calculating data and error model

	};



}

}