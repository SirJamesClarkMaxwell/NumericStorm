#pragma once
#include "Fitting.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
class NoSetModelExeption :public std::exception {

public:
	NoSetModelExeption()
	:m_message("Model to calculating the data is not setted. \n Please set model as a Model object. \n To get more information check out our documetation.") {};
	~NoSetModelExeption(){};
	const char* what()const noexcept override { return m_message.c_str(); };
private:
	std::string m_message;
};
}
}
