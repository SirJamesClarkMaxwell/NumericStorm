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
	//-SOL just check whether its a nullptr (m_referenceData.get() == nullptr)
	//NOTE we could pass the reference data as this Data, just copy them into the m_data, and evaluate points in constructor
	//-Where do you actually want to pass data, in the constructor or in the method?

	//BUG to construct the data we need the AuxilaryParameters, we must pass this as the constructor arguments
	//-where do we strore those parameters?
	
	//BUG in this implementation, we are not setting the data_valid, but we calculate the data
	//-since data is not an abstract class anymore we can just store it as plain field, not a pointer
	//-We can pass reference data as a shared pointer so we dont have to construct m_data from a vector
	//-and we can just copy the pointer into m_referenceData

	//-note in the Data class we need a way to access the vector of vectors, not only vectors inside of it
	//-because right now we cant push anything into Data
	SimplexPoint(std::shared_ptr<Data> ref_data, const std::array<double, parameter_size>& parameters)
		: m_parameters{ parameters }, m_referenceData{ ref_data }  {
		m_data = *(m_referenceData);
	}
	SimplexPoint() = default;
	SimplexPoint(const SimplexPoint<parameter_size, AuxilaryParameters>&) = default;
	SimplexPoint(SimplexPoint<parameter_size, AuxilaryParameters>&&) = default;
	SimplexPoint<parameter_size, AuxilaryParameters>& operator=(const SimplexPoint<parameter_size, AuxilaryParameters>&) = default;
	SimplexPoint<parameter_size, AuxilaryParameters>& operator=(SimplexPoint<parameter_size, AuxilaryParameters>&&) = default;

	virtual ~SimplexPoint() = default;

	//NU why we have a two of copy and move constructor?
	//-removed
	
	//Q what will happen if the unique ptr will be moved in copy/move constructor? Will we lost the data? 
	//-the unique_ptr has deleted copy constructor in its implementation, so making a default copy constructor and 
	//-then trying to use it would give compilation error, however it would not give error unless you tried to use copy constr
	//-in order to make a copy constructor, it must be defined in such a way that it creates new unique_ptr, but copies the old data
	//-Anyway since Data is not abstract we can abandon using unique_ptr
	
	//Q If we leave this copy/move constructor as it is, what will happen with other member variables? I think that they will be lost 
	//-there wouldnt be any problems with move constructor, but as I wrote the trying to use default copy constructor with unique_ptr will result in error
	
	//Proposition maybe the data should be a normal object inside the SimplexPoint it will fix our potential problem with loosing it during moving
	//-wrote it a couple of times before reaching this comment: we can make m_data a plain field, but ref data a shared pointer
	
	//NOTE At the end of the day, we always could call the move constructor explicitly, we will not have a big problem with performance 

	//-these should be removed
	//SimplexPoint(const Parameters<parameter_size, AuxilaryParameters>& params) : Parameters<parameter_size, AuxilaryParameters>(params), m_data{ std::make_unique<Data>() } {}
	//SimplexPoint(Parameters<parameter_size, AuxilaryParameters>&& params) : Parameters<parameter_size, AuxilaryParameters>(params), m_data{ std::make_unique<Data>() } {}
	bool isDataValid() const { return m_data_valid; }

private:
	//BUG we don't have a method for setting the referenceData
	//-add it
	//BUG we don't have a method for setting Model* and ErrorModel* 
	//-add them
	Parameters<parameter_size> m_parameters{};
	bool m_data_valid{ false };
	Data m_data{};
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