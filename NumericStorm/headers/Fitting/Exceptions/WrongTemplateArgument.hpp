#pragma once
#include "Fitting.hpp"
namespace NumericStorm
{
namespace Fitting
{
class WrongTemplateArgument : public std::exception
{
public:
    WrongTemplateArgument() = default;
    const char* what() const noexcept override
    {
        return "Wrong template argument, you have to provide at least one class that is derived from CreatorInterface! ";
    }
};
}
}