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
			StrategyManager(){};
			void registerStrategy(std::string name, std::unique_ptr<IDecision<paramater_size>> strategy);
			void unregisterStrategy(std::string name);
			SimplexFigure<paramater_size> makeDecision(std::string name) throw(NoAvailableStrategyException);

		private:
			std::unordered_map<std::string, std::unique_ptr<IStrategy<paramater_size>>> m_strategyList;
		};

		template <size_t paramater_size>
		void StrategyManager<paramater_size>::registerStrategy(std::string name, std::unique_ptr<IDecision<paramater_size>> strategy)
		{

			m_strategyList[name] = std::move(strategy);
		}

	}
}