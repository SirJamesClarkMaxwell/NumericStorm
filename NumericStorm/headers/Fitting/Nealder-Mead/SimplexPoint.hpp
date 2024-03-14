#pragma once
#include "../Parameters.hpp"
#include "../Model.hpp"
#include "../ErrorModel.hpp"
#include "../Exceptions/NoSetErrorModelExeption.hpp"
#include "../Exceptions/NoSetModelExeption.hpp"

#include <concepts>
#include <type_traits>
#include <memory>


namespace NumericStorm

{
namespace Fitting
{

template <std::size_t parameter_size>
class SimplexPoint {
public:

	SimplexPoint() {};
	SimplexPoint(const std::vector<double> arguments, Parameters<parameter_size > parameters, AdditionalParameters additionalParameters)
		: m_arguments(arguments), m_parameters(parameters), m_error(-1), m_modelSet(false), m_errorModelSet(false), m_additionalParameters(additionalParameters) {};

	SimplexPoint(const SimplexPoint<parameter_size>& other) = default;
	std::array<double, parameter_size> getParameters()
	{
		return m_parameters.getParameters();
	}

	// Operator overloads
	double& operator[](int index) {
		return (index >= 0 && static_cast<std::size_t>(index) < parameter_size) ? m_parameters[index] : m_parameters[0];
	}

	const double& operator[](int index) const {
		return (index >= 0 && static_cast<std::size_t>(index) < parameter_size) ? m_parameters[index] : m_parameters[0];
	}

	bool operator ==(const SimplexPoint<parameter_size>& other) const
	{
		return m_parameters.getParameters() == other.getParameters();
	}
	bool operator == (const std::array<double, parameter_size>& other) const
	{
		return m_parameters.getParameters() == other;
	};
	bool operator <=> (const SimplexPoint<parameter_size>& other) const
	{
		return m_error <=> other.m_error;
	}
	// SimplexPoint<parameter_size>& operator=(const SimplexPoint<parameter_size>& other) {
	// 	if (this != &other)
	// 	{
	// 		m_parameters = other.m_parameters;
	// 		m_error = other.m_error;
	// 	}

	// 	return *this;
	// }

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

	void setUp(std::shared_ptr<Model<parameter_size>> dataModel, std::shared_ptr<ErrorModel>errorModel) {
		setModel(dataModel);
		setErrorModel(errorModel);
	}

	void calculateError(const std::shared_ptr<Data>& referenceData) {
		if (m_errorModelSet)
		{
			if (!m_modelSet)
				throw NoSetModelExeption();
			std::shared_ptr<Data> calculatedData = std::move(calculateData());
			m_error = (*m_errorModel)(referenceData, calculatedData);
		}
		else
			throw NoSetErrorModelExeption();
	}
	std::shared_ptr<Data> calculateData() {
		if (m_modelSet)
		{
			return (*m_model)(m_arguments, m_parameters, m_additionalParameters);
		}
		else
			throw NoSetModelExeption();
	}
	double getError()const { return m_error; }
private:
	void setModel(std::shared_ptr<Model<parameter_size>> modelToSet)
	{
		m_model = modelToSet; m_modelSet = true;
	}
	void setErrorModel(std::shared_ptr<ErrorModel> modelToSet)
	{
		m_errorModel = modelToSet; m_errorModelSet = true;
	}
	std::vector<double> m_arguments;
	Parameters<parameter_size> m_parameters;
	AdditionalParameters m_additionalParameters;
	double m_error;
	bool m_modelSet;
	bool m_errorModelSet;
	std::shared_ptr<Model<parameter_size>> m_model;
	std::shared_ptr<ErrorModel> m_errorModel;

#if DEBUG
public:
	std::vector<double> getArguments() const
	{
		return m_arguments;
	}
	bool  modelIsSet() const
	{
		return m_modelSet;
	}
	bool  errorModelIsSet() const
	{
		return m_errorModelSet;
	}
	std::shared_ptr<Model<parameter_size>>  getModel() const
	{
		return m_model;
	}
	std::shared_ptr<ErrorModel> getErrorModel() const
	{
		return m_errorModel;
	}
#endif
};
}
}