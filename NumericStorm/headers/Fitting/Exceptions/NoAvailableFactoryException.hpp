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
    std::string createMessage (){
        std::string message = "Error";
        //message.append(m_factoryType);
        //message.append(" isn't available. You could forget to register concrate facotry. To see how to do it, plase check our documentation.");
    return message;
    }
};
//std::string NoAvailableFactoryException::createMessage()

}
}
