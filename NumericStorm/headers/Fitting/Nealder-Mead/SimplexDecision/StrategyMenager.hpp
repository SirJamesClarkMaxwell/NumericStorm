#include <unordered_map>
#include <string>
#include <memory>

#include "IDecision.hpp"
#include "../../Exceptions/NoAvailableStrategyException.hpp"
namespace NumericStorm
{
namespace Fitting
{
template <size_t paramater_size>
class StrategyManager
{
public:
	StrategyManager() {};
	void registerStrategy(std::string name, std::unique_ptr<IDecision<paramater_size>> strategy);
	void unregisterStrategy(std::string name);
	SimplexFigure<paramater_size> makeDecision(std::string name, std::vector<SimplexFigure<parameter_size>> simplexFigures) throw(NoAvailableStrategyException);


private:
	std::unordered_map<std::string, std::unique_ptr<IStrategy<paramater_size>>> m_strategyList;
};

template <size_t paramater_size>
void StrategyManager<paramater_size>::registerStrategy(std::string name, std::unique_ptr<IDecision<paramater_size>> strategy)
{

	m_strategyList[name.lower()] = std::move(strategy);
}
template <size_t paramater_size>
void StrategyManager<paramater_size>::unregisterStrategy(std::string name)
{
	try
	{
		m_strategyList.erase(name.lower());
	}
	catch (std::out_of_range& e)
	{
		std::cout << "I didn't find this strategy in this factory, so I can't unregister it" << std::endl;
	}
	continue;
}
template <size_t paramater_size>
SimplexFigure<paramater_size> StrategyManager<paramater_size>::makeDecision(std::string name, std::vector<SimplexFigure<parameter_size>> simplexFigures) throw(NoAvailableStrategyException)
{
	try
	{
		return m_strategyList.at(name.lower())->makeDecision(simplexFigures);
	}
		else
		{
			throw NoAvailableStrategyException(name.lower());
		}
}
}

}