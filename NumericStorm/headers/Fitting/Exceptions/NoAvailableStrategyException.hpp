
#include <exception>
#include <string>
namespace NumericStorm
{
    namespace Fitting
    {
        class NoAvailableStrategyException : public std::exception
        {
        public:
            NoAvailableStrategyException(std::string name)
                : m_message(name + " strategy is not available, you probably forgot to register it, \\\\
                    to see how to do it check our documentation. "){};
            const char *what() const noexcept override;

        private:
            std::string m_message;
        };

        const char *NoAvailableStrategyException::what() const noexcept
        {
            return m_message.c_str();
        }
    }
}