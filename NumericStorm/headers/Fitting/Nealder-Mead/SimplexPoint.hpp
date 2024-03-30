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

	SimplexPoint(const std::vector<double> arguments, const std::array<double, parameter_size>& parameters)
		: Parameters<parameter_size, AuxilaryParameters>{ parameters }, m_data{ std::make_unique<Data>(arguments) } {};
	SimplexPoint() = default;
	SimplexPoint(const SimplexPoint<parameter_size, AuxilaryParameters>&) = default;
	SimplexPoint(SimplexPoint<parameter_size, AuxilaryParameters>&&) = default;
	SimplexPoint<parameter_size, AuxilaryParameters>& operator=(const SimplexPoint<parameter_size, AuxilaryParameters>&) = default;
	SimplexPoint<parameter_size, AuxilaryParameters>& operator=(SimplexPoint<parameter_size, AuxilaryParameters>&&) = default;

	virtual ~SimplexPoint() = default;

	SimplexPoint(const Parameters<parameter_size, AuxilaryParameters>& params) : Parameters<parameter_size, AuxilaryParameters>(params), m_data{ std::make_unique<Data>() } {}
	SimplexPoint(Parameters<parameter_size, AuxilaryParameters>&& params) : Parameters<parameter_size, AuxilaryParameters>(params), m_data{ std::make_unique<Data>() } {}
	bool isDataValid() const { return m_data_valid; }

private:
	Parameters<parameter_size, AuxilaryParameters> m_parameters{};
	bool m_data_valid{ false };
	//NOTE I am not sure that storing a copy of input arguments in each simplex point is the best approach, might change later
	//NOTE we could store a reference into the data defined in the simplexFigure, or somewhere else maybe in FitterSettings or in Fitter
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