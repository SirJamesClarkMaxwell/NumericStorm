#pragma once
#include <unordered_map>
#include <string>
#include "ISimplexOperation.hpp"
#include "SimplexOperationArguments.hpp"
#include "NoAvailableFactoryException.hpp"

// TODO: change to ISimplexOperation to sharedPointer into concreate object and this should be a probably a sharedPointer


namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size>
class SimplexOperationFactory
{
public:
	SimplexOperationFactory(){};
	void registerOperation(std::string operationName, ISimplexOperation<parameter_size> operation);
	void unRegisterOperation(std::string operatioName); //throw NoAvailableFactoryException;
	ISimplexOperation<parameter_size> createOperation(std::string name, SimplexOperationArguments additionalArguments); //throw NoAvailableFactoryException;

private:
	std::unordered_map<std::string, ISimplexOperation<parameter_size>> m_listOperation;
};

template <size_t parameter_size>
void SimplexOperationFactory<parameter_size>::registerOperation(std::string operationName,
															 ISimplexOperation<parameter_size>operation)
{
	m_listOperation[operationName] = operation;
}

template <size_t parameter_size>
void SimplexOperationFactory<parameter_size>::unRegisterOperation(std::string operatioName)
{
	if (!(m_listOperation.erase(operatioName)))
		throw NoAvailableFactoryException(operatioName);
}

template <size_t parameter_size>
ISimplexOperation<parameter_size> SimplexOperationFactory<parameter_size>::createOperation(std::string operationName, SimplexOperationArguments additionalArguments)
{
	#if DEBUG
	if (true)
	{
		ISimplexOperation<parameter_size> operationObject = m_listOperation[operationName];
		auto& toReturn = operationObject(additionalArguments);
		return toReturn;
	}
	else
		throw NoAvailableFactoryException(operationName)
#endif
		auto& toReturn = m_listOperation[operationName];// (additionalArguments);
	return toReturn;
}

}
}