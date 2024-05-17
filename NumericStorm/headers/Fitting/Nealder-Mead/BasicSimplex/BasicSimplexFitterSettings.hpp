#pragma once

#include "SimplexSettings.hpp"
#include "Model.hpp"
#include "ErrorModel.hpp"
#include "SimplexOperationsHeader.hpp"
#include <ranges>
//todo we need to discus bout how we gonna implement the actual basic fitter


namespace NumericStorm::Fitting
{
template<size_t parameter_size>
class BasicSimplexFitterSettings : private SimplexSettings<parameter_size>
{
public:

	explicit BasicSimplexFitterSettings(const Model<parameter_size>& model, const ErrorModel& errorModel, long int maxIteration, double minError, std::initializer_list<double>& operationFactors)
		: SimplexSettings<parameter_size>{ model, errorModel, maxIteration, minError }, m_operationFactors{ operationFactors }{}

	/*
	BasicSimplexFitterSettings(const BasicSimplexFitterSettings<parameter_size>&) = default;
	BasicSimplexFitterSettings(BasicSimplexFitterSettings<parameter_size>&&) = default;
	BasicSimplexFitterSettings<parameter_size>& operator=(const BasicSimplexFitterSettings<parameter_size>&) = default;
	BasicSimplexFitterSettings<parameter_size>& operator=(BasicSimplexFitterSettings<parameter_size>&&) = default;
	*/

	virtual ~BasicSimplexFitterSettings() = default;
	void constructObjects();
public:


	//* operations
	std::vector<CreatorSetUpInfo<SimplexOperationSettings>> operationSetUpInfo{};

	//* simplex creators
	//todo write method for setting this in builder pattern!
	SimplexCreatorSettings creatorSettings{ "basic", 0.0 };
	Parameters<parameter_size> parametersMinBounds{  };
	Parameters<parameter_size> parametersMaxBounds{  };

	//* simplex strategies
	StrategySettings strategySettings{};

private:
	//* operations
	std::vector<double> m_operationFactors{};
	std::vector<std::string> m_operationNames{ "reflection","expansion","contraction","shrinking" };


	// todo think about the all possible settings of basic simplex fitter and set them manually
	//NOTE here we definitely need a builder pattern 


};

template<size_t parameter_size>
void BasicSimplexFitterSettings<parameter_size>::constructObjects()
{
	operationSetUpInfo.resize(m_operationNames.size());
	using std::views::zip;
	for (std::tuple<std::string&, double&> item : zip(m_operationNames, m_operationFactors))
		operationSetUpInfo.emplace_back(CreatorSetUpInfo(std::get<0>(item), std::get<1>(item)));



}
}





















