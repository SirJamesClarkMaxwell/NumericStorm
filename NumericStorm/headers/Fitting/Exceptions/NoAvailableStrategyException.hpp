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
    NoSetDataException(std::string name)
        : m_message(name + " strategy is not available, you probably forgot to register it, \\\\
            to see how to do it check our documentation. "){};
            const char* what() const noexcept override;

private:
    std::string m_message;
};

const char* NoSetDataException::what() const noexcept
{
    return m_message.c_str();
}
}
}