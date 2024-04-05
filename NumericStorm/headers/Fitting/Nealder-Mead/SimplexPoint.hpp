#pragma once
#include "../Parameters.hpp"
#include "../Data.hpp"
#include "AdditionalParameters.hpp"

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
	SimplexPoint() = delete;
	SimplexPoint(std::shared_ptr<Data> ref_data, const std::array<double, parameter_size>& parameters, AuxilaryParameters* additionalParameters)
		: m_parameters{ parameters }, m_referenceData{ ref_data } m_data {
		*ref_data
	}, m_additionalParameters{ additionalParameters } {};
		SimplexPoint(const SimplexPoint<parameter_size, AuxilaryParameters>&) = default;
		SimplexPoint(SimplexPoint<parameter_size, AuxilaryParameters>&&) = default;
		SimplexPoint<parameter_size, AuxilaryParameters>& operator=(const SimplexPoint<parameter_size, AuxilaryParameters>&) = default;
		SimplexPoint<parameter_size, AuxilaryParameters>& operator=(SimplexPoint<parameter_size, AuxilaryParameters>&&) = default;

		virtual ~SimplexPoint() = default;
		bool isDataValid() const { return m_data_valid; }
		void setModels(Model* model, ErrorModel* errorModel) { m_model = model; m_errorModel = errorModel; };
		bool evaluatePoint() {}
private:
	Parameters<parameter_size> m_parameters{};
	AuxilaryParameters* m_additionalParameters{ nullptr };

	Model<parameter_size, AuxilaryParameters>* m_model{ nullptr };
	ErrorModel* m_errorModel{ nullptr };

	double m_error{ -1 };
	std::shared_ptr<Data> m_referenceData{ nullptr };
	Data m_data{};

	bool m_calculateData();

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
template <std::size_t parameter_size, class AuxilaryParameters>
bool SimplexPoint<parameter_size, AuxilaryParameters>::m_calculateData()
{
	if (m_model == nullptr)
		return false;
	m_model(m_data, m_parameters, m_additionalParameters);
	m_data
		return true;
};
template <std::size_t parameter_size, class AuxilaryParameters>
bool SimplexPoint<parameter_size, AuxilaryParameters>::evaluatePoint()
{
	if (m_errorModel == nullptr)
		return false;
	m_calculateData(m_data, m_parameters, m_additionalParameters);
	m_error = m_errorModel(m_referenceData, m_data);
	return true;

};
}
}