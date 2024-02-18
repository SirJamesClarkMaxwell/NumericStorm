#pragma once
#include <exception>
#include <string>

namespace NumericStorm
{
namespace Fitting
{
class NoAvailableFactoryException : public std::exception
{
public:
    NoAvailableFactoryException(const std::string& factoryType) :
        m_factoryType(factoryType),m_message(createMessage()) {}

    const char* what() const noexcept override{return m_message.c_str();}


private:
    std::string m_message;
    std::string m_factoryType;
    std::string createMessage ();
};
std::string NoAvailableFactoryException::createMessage()
{
    std::string message = "This " + m_factoryType + " isn't available. You could forget to register concrate facotry. To see how to do it, plase check our documentation.";
    return message;
};

}
}
