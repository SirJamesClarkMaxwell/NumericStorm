#pragma once
#include <unordered_map>
#include <string>
#include "ISimplexOperation.hpp"
#include "SimplexOperationArguments.hpp"
namespace NumericStorm
{
namespace Fitting
{
template <size_t figure_size>
class SimplexOperationFactory 
{
public:
	SimplexOperationFactory() {};
	void registerOperation(std::string operationName, ISimplexOperation<figure_size> operation);
	void unRegisterOperation(std::string operatioName);
	ISimplexOperation<figure_size> createOperation(std::string name,SimplexOperationArguments additionalArguments);
private:
	std::unordered_map<std::string, ISimplexOperation<figure_size>> m_listOperation;
};


template<size_t figure_size>
void SimplexOperationFactory<figure_size>::registerOperation(std::string operationName, 
	ISimplexOperation<figure_size> operation)
{m_listOperation[operationName] = operation;}

template<size_t figure_size>
void SimplexOperationFactory<figure_size>::unRegisterOperation(std::string operatioName)
{m_listOperation.erase(operatioName);}

template<size_t figure_size>
ISimplexOperation<figure_size> SimplexOperationFactory<figure_size>::createOperation(std::string name,SimplexOperationArguments additionalArguments)
{
	#if DEBUG
		ISimplexOperation<figure_size> operationObject();
		auto& toReturn = operationObject.operation(additionalArguments);
		return toReturn
	#endif
	return ISimplexOperation<figure_size>().operation(additionalArguments);
}

}
}