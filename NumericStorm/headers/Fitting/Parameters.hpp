#pragma once
#include <array>
#include <iostream>
#include <stdexcept>
#include "Fitting.hpp"


namespace NumericStorm
{
namespace Fitting
{
template <size_t size_p>
class Parameters 
{

public:
	Parameters() = default;
	Parameters(std::array<double, size_p> parameters)
		:m_parameters(parameters),m_ErrorModelSet(false),m_ModelSet(false){};

	virtual double& operator [](int index) = 0;	
	virtual std::array<double, size_p> getParameters() = 0;

	virtual double getError() = 0;
	virtual void setUp() = 0;

	virtual calculateError(const Data& referanceData) = 0;


protected: 
	inline void setModel(Model modeToSet) 
		{ m_model = modelToSet; m_modelSet = true; }; 
	inline void setErrorModel(ErrorModel errorModelToSet) 
		{ m_errorModel = errorModelToSetl; m_ErrorModelSet = true; }; 

protected:
	std::array<double, size_p> m_parameters;
	double m_error;
	AdditionalParameters& m_additionalParameters; 
	Model& m_model;
	ErrorModel& m_erorModel;
	bool m_ModelSet;
	bool m_ErrorModelSet;

};
}
}