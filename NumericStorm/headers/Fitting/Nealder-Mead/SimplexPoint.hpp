#pragma once

#include <array>
#include <memory>

#include "Parameters.hpp"
#include "Data.hpp"


namespace NumericStorm::Fitting
{
template <std::size_t parameter_size>
class SimplexPoint {
public:
	SimplexPoint() = delete;
	SimplexPoint(std::shared_ptr<Data> ref_data, const std::array<double, parameter_size>& parameters)
		: m_parameters{ parameters }, m_referenceData{ ref_data }, m_data { *ref_data } {};
		SimplexPoint(const SimplexPoint<parameter_size>&) = default;
		SimplexPoint(SimplexPoint<parameter_size>&&) = default;
		SimplexPoint<parameter_size>& operator=(const SimplexPoint<parameter_size>&) = default;
		SimplexPoint<parameter_size>& operator=(SimplexPoint<parameter_size>&&) = default;

		virtual ~SimplexPoint() = default;

		template<class AuxParameters>
		void evaluatePoint(const Model<parameter_size, AuxParameters>& model, const ErrorModel& errorModel, const AuxParameters& auxParams) {
			m_calculateData(model, auxParams);
			m_error = errorModel(*m_referenceData, m_data);
		}
private:
	Parameters<parameter_size> m_parameters{};

	double m_error{ -1 };
	std::shared_ptr<Data> m_referenceData{ nullptr };
	
	Data m_data{};

	template<class AuxParameters>
	void m_calculateData(const Model<parameter_size, AuxParameters>& model, const AuxParameters& auxParams) {
		model(m_data, m_parameters, auxParams);
	}

public:
	


	bool operator ==(const SimplexPoint<parameter_size>& other) const
	{
		return this->m_parameters.getParameters() == other.getParameters();
	}
	bool operator == (const std::array<double, parameter_size>& other) const
	{
		return this->m_parameters.getParameters() == other;
	};
	bool operator <=> (const SimplexPoint<parameter_size>& other) const
	{
		return this->m_error <=> other.m_error;
	}

	virtual double& operator[](int index)
	{
		return m_parameters.at(index);
	}

	virtual const double& operator[](int index) const 
	{
		return m_parameters.at(index);
	}

	SimplexPoint<parameter_size>& operator+=(const SimplexPoint<parameter_size>& other) {
		for (std::size_t i = 0; i < parameter_size; ++i)
			this->operator[](i) += other[i];
		return *this;
	}
	SimplexPoint<parameter_size>& operator-=(const SimplexPoint<parameter_size>& other) {
		for (std::size_t i = 0; i < parameter_size; ++i)
			this->operator[](i) -= other[i];
		return *this;
	}

	SimplexPoint<parameter_size>& operator*=(double scalar) {
		for (auto& param : this->m_parameters) {
			param *= scalar;
		}
		return *this;
	}
	SimplexPoint<parameter_size>& operator/=(double scalar) {
		for (auto& param : this->m_parameters) {
			param /= scalar;
		}
		return *this;
	}

	SimplexPoint<parameter_size> operator+(const  SimplexPoint<parameter_size>& other) const {
		SimplexPoint<parameter_size> result = *this;
		result += other;
		return result;
	}
	SimplexPoint<parameter_size> operator-(const  SimplexPoint<parameter_size>& other) const {
		SimplexPoint<parameter_size> result = *this;
		result -= other;
		return result;
	}

	SimplexPoint<parameter_size> operator*(double scalar) const {
		SimplexPoint<parameter_size> result = *this;
		result *= scalar;
		return result;
	}
	SimplexPoint<parameter_size> operator/(double scalar) const {
		SimplexPoint<parameter_size> result = *this;
		result /= scalar;
		return result;
	}

};

}