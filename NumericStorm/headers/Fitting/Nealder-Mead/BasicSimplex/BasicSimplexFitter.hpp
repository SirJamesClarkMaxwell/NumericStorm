#pragma once

#include "SimplexFigure.hpp"
#include "SimplexFitter.hpp"
#include "BasicSimplexFitterSettings.hpp"
#include "SimplexOperationsHeader.hpp"
#include "SimplexCreatorFactory.hpp"
#include "StrategyManager.hpp"
#include "BasicSimplexCreator.hpp"

//todo manage includes!
//todo make a nspch.h file
namespace NumericStorm::Fitting
{
template <size_t parameter_size, class AxularyParameters = AdditionalParameters, class DerivedSettings = BasicSimplexFitterSettings<parameter_size>>
class BasicSimplexFitter : public SimplexFitter<parameter_size, AxularyParameters, DerivedSettings>
{
public:
	BasicSimplexFitter() = delete; //todo set default configuration here
	BasicSimplexFitter(const DerivedSettings& settings, bool calculateUncertainty = false)
		:SimplexFitter<parameter_size, AxularyParameters, DerivedSettings>{ settings, calculateUncertainty }
	{

	};
	/*
	BasicSimplexFitter(const BasicSimplexFitter<parameter_size, DerivedSettings>&) = default;
	BasicSimplexFitter(BasicSimplexFitter<parameter_size, DerivedSettings>&&) = default;
	BasicSimplexFitter<parameter_size, DerivedSettings>& operator=(const BasicSimplexFitter<parameter_size, DerivedSettings>&) = default;
	BasicSimplexFitter<parameter_size, DerivedSettings>& operator=(BasicSimplexFitter<parameter_size, DerivedSettings>&&) = default;
	*/

	virtual ~BasicSimplexFitter() = default;

	BasicSimplexFitter(SimplexFigure<parameter_size> simplexFigure)
		: SimplexFitter<parameter_size>{ simplexFigure } {}

	virtual void setUp() override
	{
		//* operations
		std::vector<CreatorSetUpInfo<SimplexOperationSettings>> operationSettings = this->m_settings->operationSetUpInfo;
		this->m_simplexOperationFactory.registerCreators<Reflection, Expansion, Contraction, Shrinking>(operationSettings);

		//* creators
		this->m_simplexCreatorFactory.registerCreators<BasicSimplexCreator<parameter_size, >>(this->m_settings->creatorSettings);

		//* strategy
		this->m_strategyManager.registerStrategy<BasicSimplexStrategy<parameter_size, >>(this->m_settings->strategySettings);
	};
	virtual FittingResults<parameter_size> fit() override {
		// The fit method will be in a wrapper of this class written by the user
		//todo move definition of minimize method below the class
		int iterationCount = 0;
		//NOTE ohhh this long invoking things aren't good, I would store this in local variables

		//todo divide this into sections
		//todo extract methods
		//todo clean the naming convention 

		SimplexIntermediatePoints simplexIntermediatePoints;
		while (checkFittingConditions(iterationCount)) {
			this->m_simplexFigure.sort();

			do {

			} while (true);
		}

		SimplexPoint<parameter_size> bestPoint = simplexIntermediatePoints[bestPoint];
		FittingResults<parameter_size> fittingResult{ bestPoint.getParameters(), iterationCount, bestPoint.getError() };
		return fittingResult;
	};

private:
	const bool checkFittingConditions(int& iter)
	{
		bool iterationCondition = iter++ <= this->m_settings->getMaxIteration();
		bool errorCondition = this->m_simplexFigure[parameter_size] <= this->m_settings->getMinError();
		return iterationCondition && errorCondition;
	}
	//auto setUpFittingsProcedure() {};
	//todo add oneStep method and call it in minimize it, make it public in the debug configuration





};


//todo implement the setUp function based on the Fitter settings
	//* setUp function
	//todo initialize settings of the creators, fill the settings
	//todo initialize factories
	//todo register the creators


}