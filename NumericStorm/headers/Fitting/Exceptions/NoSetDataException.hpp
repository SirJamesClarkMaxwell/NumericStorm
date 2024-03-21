#pragma once
#include <exception>
#include <string>
namespace NumericStorm
{
namespace Fitting
{
class NoSetDataException : public std::exception
{
public:
    NoSetDataException()
        : m_message("You tried to calculate error in SimplexFigure class without set the data as a reference Data. \\\\
            To see how to do it check our documentation. "){};
            const char* what() const noexcept override { return m_message.c_str(); };

private:
    std::string m_message;
};

}
}