#pragma once
#include "../SimplexFigure.hpp"
#include "../SimplexPoint.hpp"

#include "ISimplexFactory.hpp"

namespace NumericStorm 
{
namespace Fitting 
{

struct SimplexUpdateFactory
{
	std::string name;
	SimplexCreatorSettigns settings;

};


template<size_t figure_size>
class SimplexCreatorFactory 
{
public:
	SimplexCreatorFactory() {};
	void registerNewFactory(std::string name, ISimplexFactory<figure_size>* factory,SimplexCreatorSettigns settings); 
	void unRegisterFactory(std::string name);
	SimplexFigure<figure_size> createNewSimplex(std::string name,SimplexPoint<figure_size-1> basedPoint);
	void updateFactoriesSettings(std::vector<SimplexUpdateFactory> newSetttings);
private:
	std::unordered_map<std::string,ISimplexFactory<figure_size>*> m_avliableFactories;
};


template< size_t figure_size>
void SimplexCreatorFactory<figure_size>::registerNewFactory(std::string name, ISimplexFactory<figure_size>* factory,SimplexCreatorSettigns settings)
	{m_avliableFactories[name] = factory(settings);};

template<size_t figure_size>
void SimplexCreatorFactory<figure_size>::unRegisterFactory(std::string name)
	{m_avliableFactories.erase(name); };

template<size_t figure_size>
SimplexFigure<figure_size> SimplexCreatorFactory<figure_size>::createNewSimplex(std::string name, SimplexPoint<figure_size-1> basedPoint)
{
	ISimplexFactory factory = m_avliableFactories[name];
	return factory(basedPoint);
};

template<size_t figure_size>
void SimplexCreatorFactory<figure_size>::updateFactoriesSettings(std::vector<SimplexUpdateFactory> newSettings)
{
	for (auto& item : newSettings)
	{
		ISimplexFactory<figure_size>* facotry = m_avliableFactories[item.name]; 
		factory->updateSettigns(newSettings);
	}
};

}
}