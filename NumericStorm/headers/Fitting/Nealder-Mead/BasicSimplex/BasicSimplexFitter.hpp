#pragma once

#include "../SimplexFigure.hpp"
#include "../SimplexFitter.hpp"
#include "../SimplexPoint.hpp"
#include "BasicSimplexFitterSettings.hpp"
#include "../SimplexOperations/SimplexOperationsHeader.hpp"
#include "../SimplexCreator/SimplexCreatorFactory.hpp"
#include "../SimplexDecision/StrategyManager.hpp"

//todo manage includes!
//todo make a nspch.h file
namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size, class DerivedSettings = BasicSimplexFitterSettings<parameter_size>>
class BasicSimplexFitter : public SimplexFitter<parameter_size, DerivedSettings>
{
public:
	BasicSimplexFitter() = delete; //todo set default configuration here
	BasicSimplexFitter(const BasicSimplexFitter<parameter_size, DerivedSettings>&) = default;
	BasicSimplexFitter(BasicSimplexFitter<parameter_size, DerivedSettings>&&) = default;
	BasicSimplexFitter<parameter_size, DerivedSettings>& operator=(const BasicSimplexFitter<parameter_size, DerivedSettings>&) = default;
	BasicSimplexFitter<parameter_size, DerivedSettings>& operator=(BasicSimplexFitter<parameter_size, DerivedSettings>&&) = default;

	virtual ~BasicSimplexFitter() = default;

	BasicSimplexFitter(SimplexFigure<parameter_size> simplexFigure)
		: SimplexFitter<parameter_size>{ simplexFigure } {}

	virtual void setUp() override {
		//todo move definition of setUp method below the class
		//NOTE more things should be there
		/*
		because this is the class that user will use and we know the exact type of things
		we could fix some things and
		*/
	}
	virtual void fit() override {
		//NOTE this method should be called minimize, not fit. 
		// The fit method will be in a wrapper of this class written by the user
		//todo move definition of minimize method below the class
		int iter = 0;
		//NOTE ohhh this long invoking things aren't good, I would store this in local variables
		//todo divide this into sections
		//todo extract methods
		//todo clean the naming convention 
		while (iter++ <= this->m_settings->getMaxIteration() && this->m_simplexFigure[parameter_size] <= this->m_settings->getMinError()) {
			this->m_simplexFigure.sort();

			do {

			} while (true);
		}
	}

private:
	auto setUpFittingsProcedure() {};
	//todo add oneStep method and call it in minimize it, make it public in the debug configuration
};

}
}