#pragma once
#include <unordered_map>
#include <string>
#include "ISimplexOperation.hpp"
#include "SimplexOperationSettigns.hpp"
#include "NoAvailableFactoryException.hpp"



namespace NumericStorm
{
namespace Fitting
{

template <size_t parameter_size>
class SimplexOperationFactory
{
	using ISimplexOperation_ptr = std::shared_ptr<ISimplexOperation<parameter_size>>;
public:
	SimplexOperationFactory() {};
	void registerOperation(std::string operationName, ISimplexOperation_ptr operation);
	void unRegisterOperation(std::string operatioName) throw (NoAvailableFactoryException);
	SimplexFigure<parameter_size> createOperation(std::string name, const SimplexFigure<parameter_size> simplexFigure) throw (NoAvailableFactoryException);
	void updateOperationSettings(std::string operationName, SimplexOperationSettigns newSettings)throw (NoAvailableFactoryException);

private:
	std::unordered_map<std::string, ISimplexOperation_ptr> m_listOperation;
};

template <size_t parameter_size>
void SimplexOperationFactory<parameter_size>::registerOperation(std::string operationName, ISimplexOperation_ptr operation)
	{m_listOperation[operationName] = operation;}

template <size_t parameter_size>
void SimplexOperationFactory<parameter_size>::unRegisterOperation(std::string operatioName)
{
	if (!(m_listOperation.erase(operatioName)))
		throw NoAvailableFactoryException(operatioName);
};

template <size_t parameter_size>
SimplexFigure<parameter_size> SimplexOperationFactory<parameter_size>::createOperation(std::string name, const SimplexFigure<parameter_size> simplexFigure)
{
	ISimplexOperation_ptr simplexOperation = m_listOperation.find(name);

	if (simplexOperation != m_listOperation.end())
		return  simplexOperation->second(simplexFigure);
	else
		throw NoAvailableFactoryException(name);
};
}
}