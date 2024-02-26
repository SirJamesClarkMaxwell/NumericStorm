#pragma once

#include "Fitting.hpp"

namespace NumericStorm 
{
namespace Fitting 
{

class NoSetErrorModelExeption : public std::exception
{
public:
	NoSetErrorModelExeption()
	:m_message("Function to calculating the error is not setted. \n Please set this error model as an object of ErrorModel. You could use one of our predefided error model. \n To get more information check out our documentation!") {};
	~NoSetErrorModelExeption() {};
	const char* what() const noexcept override {return m_message.c_str(); };
private:
	std::string m_message;
};
}
}