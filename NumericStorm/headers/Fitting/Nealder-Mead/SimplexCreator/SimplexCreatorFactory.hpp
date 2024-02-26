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
	SimplexCreatorSettigns settings;

};

template<size_t figure_size>
class SimplexCreatorFactory 
{
//using std::unique_ptr<ISimplexFactory<figure_size>> = std::function<std::unique_ptr<ISimplexFactory<figure_size>>()>;
public:
	SimplexCreatorFactory() {};
	void registerNewFactory(std::string operationName, std::unique_ptr<ISimplexFactory<figure_size>> factory,SimplexCreatorSettigns settings); 
	void unRegisterFactory(std::string operationName);
	SimplexFigure<figure_size> createNewSimplex(std::string operationName,SimplexPoint<figure_size-1> basedPoint);
	void updateFactoriesSettings(std::vector<SimplexUpdateFactory> newSetttings);
private:
	std::unordered_map<std::string,std::unique_ptr<ISimplexFactory<figure_size>>> m_avliableFactories;
	bool checkInAvliable(std::string operationName);
};


template< size_t figure_size>
void SimplexCreatorFactory<figure_size>::registerNewFactory(std::string operationName, std::unique_ptr<ISimplexFactory<figure_size>> factory,SimplexCreatorSettigns settings)
	{m_avliableFactories[operationName] = factory(settings);};

template<size_t figure_size>
void SimplexCreatorFactory<figure_size>::unRegisterFactory(std::string operationName)
{
	if (checkInAvliable(operationName))
		m_avliableFactories.erase(operationName);
	else
		continue;
};

template<size_t figure_size>
SimplexFigure<figure_size>SimplexCreatorFactory<figure_size>::createNewSimplex(std::string operationName, SimplexPoint<figure_size-1> basedPoint)
{
	
};

template<size_t figure_size>
void SimplexCreatorFactory<figure_size>::updateFactoriesSettings(std::vector<SimplexUpdateFactory> newSettings)
{
	for (auto& item : newSettings)
	{
		ISimplexFactory<figure_size>& factory = *m_avliableFactories[item.operationName]; 
		factory.updateSettigns(item.settings);
	}
};
template<size_t figure_size>
bool SimplexCreatorFactory<figure_size>::checkInAvliable(std::string operationName) 
{
	return m_avliableFactories.find(operationName) == m_avliableFactories.end();
};
}
}