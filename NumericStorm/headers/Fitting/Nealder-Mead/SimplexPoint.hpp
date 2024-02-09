#pragma once
#include "Fitting.hpp" 

namespace NumericStorm 
{
namespace Fitting 
{
template< size_t size_p>
class SimplexPoint :public Parameters <size_p>
{
public:
	SimplexPoint() = default;
	SimplexPoint(std::array<double, size_p> parameters)
		:Paramters<size_p>(parameters) {};
	double& operator[](int index)
	{
		if (index >= size_p) { return this->m_parameters[0]; }
		return this->m_parameters[index];
	}
	const double& operator[](int index) const
	{
		if (index >= size_p) { return this->m_parameters[0]; }
		return this->m_parameters[index];
	}

	bool operator ==(const Parameters<size_p>& other) const
	{
		return this->m_parameters == other.getParameters();
	}

	bool operator ==(const std::array<double, size_p>& other) const
	{
		return this->m_parameters == other;
	}

	template<typename T_o>
	Parameters<size_p>& operator = (const Parameters<size_p>& other)
	{
		if (this == &other)
			return *this;
		this->m_parameters = other.getParameters();
		return *this;
	}

	template<typename T_o>
	Parameters<size_p>& operator += (const Parameters<size_p>& other)
	{
		for (size_t i = 0; i < size_p; i++)
			this->m_parameters[i] += other[i];
		return *this;
	}

	template <typename T>
		requires (std::is_arithmetic_v<T>)
	Parameters<size_p>& operator += (const T& other)
	{
		for (size_t i = 0; i < size_p; i++)
			this->m_parameters[i] += other;
		return *this;
	}
	template<typename T_o>
	Parameters<size_p>& operator -= (const Parameters<size_p>& other)
	{
		for (size_t i = 0; i < size_p; i++)
			this->m_parameters[i] -= other[i];
		return *this;
	};

	template <typename T>
		requires (std::is_arithmetic_v<T>)
	Parameters<size_p>& operator -= (const T& other)
	{
		for (size_t i = 0; i < size_p; i++)
			this->m_parameters[i] -= other;
		return *this;
	};
	Parameters<size_p>& operator *= (const auto& other)
	{
		for (size_t i = 0; i < size_p; i++)
			this->m_parameters[i] *= other;
		return *this;
	};
	Parameters<size_p>& operator /= (const auto& other)
	{
		for (size_t i = 0; i < size_p; i++)
			this->m_parameters[i] /= other;
		return *this;
	};

	template<typename T_o>
	Parameters<size_p> operator + (const Parameters<size_p>& other) const
	{
		auto result = *this;
		result += other;
		return result;
	};
	template<typename T_o>
	Parameters<size_p> operator - (const Parameters<size_p>& other)const
	{
		auto result = *this;
		result -= other;
		return result;
	};

	inline Parameters<size_p> operator + (const auto& other) const
	{
		auto result = *this; result += other; return result;
	};
	inline Parameters<size_p> operator - (const auto& other) const
	{
		auto result = *this; result -= other; return result;
	};
	inline Parameters<size_p> operator * (const auto& other) const
	{
		auto result = *this; result *= other; return result;
	};
	inline Parameters<size_p> operator / (const auto& other) const
	{
		auto result = *this; result /= other; return result;
	};

};


}

}