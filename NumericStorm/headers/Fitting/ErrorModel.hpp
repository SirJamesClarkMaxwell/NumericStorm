#pragma once
#include "Fitting.hpp"


namespace NumericStorm 
{
namespace Fitting 
{

class ErrorModel 
{

public:
	ErrorModel() = default;
	ErrorModel(std::function<double(const Data&, const Data&)> errorModel)
		:m_errorModel(errorModel){};
	~ErrorModel() {};
	virtual double operator()(const Data& referencedData, const Data& comparedData) = 0;
protected:
	std::function<double(const Data& referenceData, const Data& comparedData)> m_errorModel;
};


}
}