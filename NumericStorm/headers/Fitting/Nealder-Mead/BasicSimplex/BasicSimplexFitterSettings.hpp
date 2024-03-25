#pragma once
#include <memory>
#include "../../Model.hpp"
#include "../../ErrorModel.hpp"
#include "../SimplexFitterSettings.hpp"
#include "../SimplexOperations/SimplexOperationsHeader.hpp"
#include "../SimplexDecision/StrategyManager.hpp"
#include "../SimplexDecision/BasicSimplexStrategy.hpp"
#include "../SimplexCreator/SimplexCreatorFactory.hpp"
namespace NumericStorm
{
namespace Fitting
{
enum GreedyApproach
{
	minimization,
	expansion
};
template<size_t parameter_size>
class BasicSimplexFitterSettings :SimplexFitterSettings<parameter_size>
{
public:
	BasicSimplexFitterSettings(std::unique_ptr<Model<parameter_size>> model, std::unique_ptr<ErrorModel> errorModel, GreedyApproach greedyApproach = expansion)
		:SimplexFitterSettings<parameter_size>(model, errorModel), m_greedyApproach(greedyApproach)
	{
		setUpSimplexOperationFactory();
		setUpStrategyManager();
	}


	StrategyManager<parameter_size> getStrategyManager() { return m_basicStrategy.getStrategyManager(); }
	m_simplexOperationFactory<parameter_size> getSimplexOperationFactory() { return m_simplexOperationFactory };
private:
	GreedyApproach m_greedyApproach = expansions;
	StrategyManager<parameter_size> m_strategyManager();
	SimplexOperationFactory m_simplexOperationFactory();
	SimplexCreatorFactory<parameter_size> m_simplexCreatorFactory();
	void createSimplexOperationSettings(const std::vector<double> factors)
	{
		std::vector<SimplexOperationSettings> simplexOperationsSettings;
		for (int i = 0;i < 4;i++)
			simplexOperationsSettings.push_back(SimplexOperationSettings(factors[i]));
		return simplexOperationsSettings;
	};
	virtual void setUpSimplexOperationFactory()override
	{
		std::array<double, 4> numbersToOperationsSettings{ 1,0.5,2,0.5 };
		std::array<SimplexOperationsSettings, 4> simplexOperationsArguments = createSimplexOperationSettings(numbersToOperationsSettings);

		std::array<std::string, 4> operationNames{ "reflection","expansion","contraction","shrinking" };
		std::array<std::unique_ptr<ISimplexOPeration<parameter_size>>, 4> operations;
		operations[0] = std::make_unique < Reflection<parameter_size>(simplexOperationsArguments[0]);
		operations[1] = std::make_unique < Expansion<parameter_size>(simplexOperationsArguments[1]);
		operations[2] = std::make_unique < Contraction<parameter_size>(simplexOperationsArguments[2]);
		operations[3] = std::make_unique < Shrinking<parameter_size>(simplexOperationsArguments[3]);
		for (int i = 0; i < simplexOperationsArguments.size();i++)
			m_simplexOperationFactory.registerOperation(operationNames[i], std::move(operations[i]));
	};
	virtual void setUpStrategyManager()override
	{
		m_strategyManager = StrategyManager<parameter_size>();
		m_strategyManager.registerStrategy("basicSimplexStrategy", std::make_unique<BasicSimplexStrategy>(m_greedyApproach));
	}
	virtual void setUpSimplexCreatorFactory()override
	{
		//TODO: implement setUpSimplexCreatorFactory method
	}



};


}
}