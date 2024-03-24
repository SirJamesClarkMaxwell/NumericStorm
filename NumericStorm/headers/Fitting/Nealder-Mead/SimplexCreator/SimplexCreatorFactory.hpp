#pragma once
#include "../SimplexFigure.hpp"
#include "../SimplexPoint.hpp"

#include "ISimplexFactory.hpp"
#include "../../Exceptions/NoAvailableFactoryException.hpp"

namespace NumericStorm
{
namespace Fitting
{

struct SimplexUpdateFactory
{
	std::string operationName;
	SimplexCreatorSettings settings;

};

template<size_t parameter_size>
class SimplexCreatorFactory
{
	//using std::unique_ptr<ISimplexFactory<parameter_size>> = std::function<std::unique_ptr<ISimplexFactory<parameter_size>>()>;
public:
	SimplexCreatorFactory() {};
	void registerNewFactory(std::string operationName, std::unique_ptr<ISimplexFactory<parameter_size>> factory);
	void unRegisterFactory(std::string operationName);
	SimplexFigure<parameter_size> createNewSimplex(std::string operationName, SimplexPoint<parameter_size > basedPoint);
	void updateFactoriesSettings(std::vector<SimplexUpdateFactory> newSettings);
private:
	std::unordered_map<std::string, std::unique_ptr<ISimplexFactory<parameter_size>>> m_availableFactories;
	bool checkInAvailable(std::string operationName);
	//TODO reimplement checkInAvaliable method
};


template< size_t parameter_size>
void SimplexCreatorFactory<parameter_size>::registerNewFactory(std::string operationName, std::unique_ptr<ISimplexFactory<parameter_size>> factory, SimplexCreatorSettings settings)
{
	m_availableFactories[operationName] = factory(settings);
};

template<size_t parameter_size>
void SimplexCreatorFactory<parameter_size>::unRegisterFactory(std::string operationName)
{
	if (checkInAvailable(operationName))
		m_availableFactories.erase(operationName);
	else
		continue;
};

template<size_t parameter_size>
SimplexFigure<parameter_size>SimplexCreatorFactory<parameter_size>::createNewSimplex(std::string operationName, SimplexPoint<parameter_size > basedPoint)
{

};

template<size_t parameter_size>
void SimplexCreatorFactory<parameter_size>::updateFactoriesSettings(std::vector<SimplexUpdateFactory> newSettings)
{
	for (auto& item : newSettings)
	{
		ISimplexFactory<parameter_size>& factory = *m_availableFactories[item.operationName];
		factory.updateSettings(item.settings);
	}
};
template<size_t parameter_size>
bool SimplexCreatorFactory<parameter_size>::checkInAvailable(std::string operationName)
{
	return m_availableFactories.find(operationName) == m_availableFactories.end();
};
}
}