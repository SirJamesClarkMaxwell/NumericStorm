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
template <std::size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class SimplexPoint {
public:
	//BUG we need a variable for storing the status of referenceData pointer if we are not passing it into the constructor
	//NOTE we could pass the reference data as this Data, just copy them into the m_data, and evaluate points in constructor

	//BUG to construct the data we need the AuxilaryParameters, we must pass this as the constructor arguments
	//BUG in this implementation, we are not setting the data_valid, but we calculate the data
	SimplexPoint(const std::vector<double> arguments, const std::array<double, parameter_size>& parameters)
		: Parameters<parameter_size>{ parameters }, m_data{ std::make_unique<Data>(arguments) } {};
	SimplexPoint() = default;
	SimplexPoint(const SimplexPoint<parameter_size, AuxilaryParameters>&) = default;
	SimplexPoint(SimplexPoint<parameter_size, AuxilaryParameters>&&) = default;
	SimplexPoint<parameter_size, AuxilaryParameters>& operator=(const SimplexPoint<parameter_size, AuxilaryParameters>&) = default;
	SimplexPoint<parameter_size, AuxilaryParameters>& operator=(SimplexPoint<parameter_size, AuxilaryParameters>&&) = default;

	virtual ~SimplexPoint() = default;

	//NU why we have a two of copy and move constructor?
	//Q what will happen if the unique ptr will be moved in copy/move constructor? Will we lost the data? 
	//Q If we leave this copy/move constructor as it is, what will happen with other member variables? I think that they will be lost 
	//Proposition maybe the data should be a normal object inside the SimplexPoint it will fix our potential problem with loosing it during moving
	//NOTE At the end of the day, we always could call the move constructor explicitly, we will not have a big problem with performance 
	SimplexPoint(const Parameters<parameter_size, AuxilaryParameters>& params) : Parameters<parameter_size, AuxilaryParameters>(params), m_data{ std::make_unique<Data>() } {}
	SimplexPoint(Parameters<parameter_size, AuxilaryParameters>&& params) : Parameters<parameter_size, AuxilaryParameters>(params), m_data{ std::make_unique<Data>() } {}
	bool isDataValid() const { return m_data_valid; }

private:
	//BUG we don't have a method for setting the referenceData
	//BUG we don't have a method for setting Model* and ErrorModel* 
	Parameters<parameter_size> m_parameters{};
	bool m_data_valid{ false };
	std::unique_ptr<Data> m_data{ nullptr };
	std::shared_ptr<Data> m_referenceData{ nullptr };
	double m_error{ -1 };
	Model<parameter_size, AuxilaryParameters>* m_model{ nullptr };
	ErrorModel* m_errorModel{ nullptr };

public:
	bool operator ==(const SimplexPoint<parameter_size, AuxilaryParameters>& other) const
	{
		return this->m_parameters.getParameters() == other.getParameters();
	}
	bool operator == (const std::array<double, parameter_size>& other) const
	{
		return this->m_parameters.getParameters() == other;
	};
	bool operator <=> (const SimplexPoint<parameter_size, AuxilaryParameters>& other) const
	{
		return this->m_error <=> other.m_error;
	}

	virtual double& operator[](int index) override
	{
		m_data_valid = false;
		//todo add model, error model, and recalculating the data after change of parameters
		return m_parameters[index];
	}

	SimplexPoint<parameter_size, AuxilaryParameters>& operator+=(const SimplexPoint<parameter_size, AuxilaryParameters>& other) {
		for (std::size_t i = 0; i < parameter_size; ++i)
			this->operator[](i) += other[i];
		return *this;
	}
	SimplexPoint<parameter_size, AuxilaryParameters>& operator-=(const SimplexPoint<parameter_size, AuxilaryParameters>& other) {
		for (std::size_t i = 0; i < parameter_size; ++i)
			this->operator[](i) -= other[i];
		return *this;
	}

	SimplexPoint<parameter_size, AuxilaryParameters>& operator*=(double scalar) {
		for (auto& param : this->m_parameters) {
			param *= scalar;
		}
		return *this;
	}
	SimplexPoint<parameter_size, AuxilaryParameters>& operator/=(double scalar) {
		for (auto& param : this->m_parameters) {
			param /= scalar;
		}
		return *this;
	}

	SimplexPoint<parameter_size, AuxilaryParameters> operator+(const  SimplexPoint<parameter_size, AuxilaryParameters>& other) const {
		SimplexPoint<parameter_size, AuxilaryParameters> result = *this;
		result += other;
		return result;
	}
	SimplexPoint<parameter_size, AuxilaryParameters> operator-(const  SimplexPoint<parameter_size, AuxilaryParameters>& other) const {
		SimplexPoint<parameter_size, AuxilaryParameters> result = *this;
		result -= other;
		return result;
	}

	SimplexPoint<parameter_size, AuxilaryParameters> operator*(double scalar) const {
		SimplexPoint<parameter_size, AuxilaryParameters> result = *this;
		result *= scalar;
		return result;
	}
	SimplexPoint<parameter_size, AuxilaryParameters> operator/(double scalar) const {
		SimplexPoint<parameter_size, AuxilaryParameters> result = *this;
		result /= scalar;
		return result;
	}

};
}
}