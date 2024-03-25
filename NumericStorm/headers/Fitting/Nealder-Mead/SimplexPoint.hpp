#pragma once
#include "../Parameters.hpp"
#include "../Data.hpp"

#include <vector>
#include <array>
#include <memory>


namespace NumericStorm

{
namespace Fitting
{


template <std::size_t parameter_size>
class SimplexPoint : public Parameters<parameter_size> {
public:

	SimplexPoint() = default;
	SimplexPoint(const SimplexPoint<parameter_size>&) = default;
	SimplexPoint(SimplexPoint<parameter_size>&&) = default;
	SimplexPoint<parameter_size>& operator=(const SimplexPoint<parameter_size>&) = default;
	SimplexPoint<parameter_size>& operator=(SimplexPoint<parameter_size>&&) = default;

	virtual ~SimplexPoint() = default;

	SimplexPoint(const Parameters<parameter_size>& params) : Parameters<parameter_size>(params), m_data{std::make_unique<Data>() } {}
	SimplexPoint(Parameters<parameter_size>&& params) : Parameters<parameter_size>(params), m_data{ std::make_unique<Data>() } {}


	SimplexPoint(const std::vector<double> arguments, const std::array<double, parameter_size>& parameters)
		: Parameters<parameter_size>{ parameters }, m_data{ std::make_unique<Data>(arguments) } {};



	const Data& getData() const { return *(m_data); }
	Data& getData() { m_data_valid = true; return *(m_data); }


	bool isDataValid() const { return m_data_valid; }


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

	virtual double& operator[](int index) override
	{
		//overloading to add data invalidation
		m_data_valid = false;
		//instead of rewriting the entire operator we add functionality and call operator of the base class
		return Parameters<parameter_size>::operator[](index);
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
	SimplexPoint<parameter_size>& operator*=(const  SimplexPoint<parameter_size>& other) {
		for (std::size_t i = 0; i < parameter_size; ++i)
			this->operator[](i) *= other[i];
		return *this;
	}
	SimplexPoint<parameter_size>& operator/=(const  SimplexPoint<parameter_size>& other) {
		for (std::size_t i = 0; i < parameter_size; ++i)
			this->operator[](i) /= other[i];
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
	SimplexPoint<parameter_size> operator*(const  SimplexPoint<parameter_size>& other) const {
		SimplexPoint<parameter_size> result = *this;
		result *= other;
		return result;
	}
	SimplexPoint<parameter_size> operator/(const  SimplexPoint<parameter_size>& other) const {
		SimplexPoint<parameter_size> result = *this;
		result /= other;
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

private:
	bool m_data_valid{ false };
	//I am not sure that storing a copy of input arguments in each simplex point is the best approach, might change later
	std::unique_ptr<Data> m_data{ nullptr };
};
}
}