#pragma once

#include <array>
#include <memory>
#include <ranges>
#include <utility>

#include "Parameters.hpp"
#include "Data.hpp"


namespace NumericStorm::Fitting
{
	template <size_t parameter_size>
	class SimplexPoint {
	public:
		using CallbackType = std::function<void(SimplexPoint<parameter_size>&)>;
	
		SimplexPoint() = default;
		SimplexPoint(const SimplexPoint<parameter_size>& other) = default;
		SimplexPoint(SimplexPoint<parameter_size>&& other) = default;

		SimplexPoint& operator=(const SimplexPoint<parameter_size>& other) = default;
		SimplexPoint& operator=(SimplexPoint<parameter_size>&& other) = default;

		SimplexPoint(const Parameters<parameter_size>& parameters)
			: m_parameters{ parameters } {};
	
		virtual ~SimplexPoint() = default;
		double& getError() { return m_error; }
		const double& getError() const { return m_error; }
		void setError(double error) { m_error = error; }
		bool hasCallback() const { return m_evalCallback != nullptr; }
		auto& getCallback() const { return m_evalCallback; }
	
		const Data& getData() const { return m_data; }
		Data& getData() { return m_data; }
	
		const auto& getParameters() const {
			return m_parameters;
		}

		auto& getParameters() {
			return m_parameters;
		}
	
		void setParameters(const Parameters<parameter_size>& parameters, bool evaluate = true) {
			m_parameters = parameters;
			if (evaluate) evaluatePoint();
		}
	
		void evaluatePoint() {
			m_evalCallback(*this);
		}
	
		void onEvaluate(const CallbackType& cb) {
			m_evalCallback = cb;
		}
	
		auto begin() { return m_parameters.begin(); }
		auto end() { return m_parameters.end(); }
		auto begin() const { return m_parameters.begin(); }
		auto end() const { return m_parameters.end(); }
		auto cbegin() const { return m_parameters.cbegin(); }
		auto cend() const { return m_parameters.cend(); }
	protected:
		Parameters<parameter_size> m_parameters{};
	
		double m_error{ -1 };
	
		Data m_data{};
	
		CallbackType m_evalCallback{};
	
	
	
	public:
	
	
		auto operator <=> (const SimplexPoint<parameter_size>& other) const
		{
			return this->m_error <=> other.m_error;
		}
	
		double& operator[](size_t index)
		{
			return m_parameters[index];
		}
	
		const double& operator[](size_t index) const
		{
			return m_parameters[index];
		}
	
		SimplexPoint<parameter_size>& operator+=(const SimplexPoint<parameter_size>& other) {
			for (auto [a, b] : std::ranges::views::zip(m_parameters, other.m_parameters)) {
				a += b;
			}
			return *this;
		}
		SimplexPoint<parameter_size>& operator-=(const SimplexPoint<parameter_size>& other) {
			for (auto [a, b] : std::ranges::views::zip(m_parameters, other.m_parameters)) {
				a -= b;
			}
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