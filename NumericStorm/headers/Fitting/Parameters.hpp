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
	bool setModel() {}; //<- add argumetns
	bool setErrorModel() {}; //<- add argumetns
	std::array<double, size_p> m_parameters;
	double m_error;
	auto m_additionalArguments; // <- change to additionalArgumetns
	auto m_model;// <- change to model
	auto m_errorModel;// <- change to errorModel
	bool m_ModelSet;
	bool m_ErrorModelSet;

};
}
}