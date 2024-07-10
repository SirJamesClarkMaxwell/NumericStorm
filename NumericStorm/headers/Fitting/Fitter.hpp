#pragma once
#include <memory>
#include <concepts>

#include "AdditionalParameters.hpp"
#include "OptimizerSettings.hpp"
#include "Parameters.hpp"
#include "FittingResults.hpp"
#include "UncertaintyCalculator.hpp"
namespace NumericStorm::Fitting {

template<class DecoratedOptimizer, class OptimizingType, class SetUpOutput>
concept Optimizer = requires (
	DecoratedOptimizer optimizer, OptimizingType & initialParameters,
	Data & fittingData,
	AdditionalParameters additionalParameters, FittingResults<OptimizingType> result,
	SetUpOutput output
	)
{
	{ optimizer.setUpFittingProcedure(initialParameters, fittingData, additionalParameters) }-> std::convertible_to<SetUpOutput>;
	{ optimizer.checkStopConditions() }-> std::convertible_to<bool>;
	{ optimizer.oneStepAlgorithm(output) }-> std::convertible_to<void>;
	{ optimizer.calculateUncertainty() }-> std::convertible_to<void>;
	{ optimizer.getResult() }-> std::convertible_to<OptimizingType&>;
};



template<class DecoratedOptimizer, class OptimizingType, class SetUpOutput, class AuxilaryParameters>
	requires Optimizer<DecoratedOptimizer, OptimizingType, SetUpOutput>&&
UncertaintyStrategyWrapper<OptimizingType>

class Fitter
{
public:
	explicit Fitter(const Optimizer& optimizer, bool calculateUncertainty = false)
		: m_optimizer{ optimizer }, m_calculateUncertainty{ calculateUncertainty } {};

	FittingResults<OptimizingType> fit(const OptimizingType& initialParameters, const Data& fittingData,
		const AuxilaryParameters& additionalParameters);
	void setUncertaintyCalculator(UncertaintyStrategyWrapper uncertaintyCalculator) { m_uncertaintyCalculator = uncertaintyCalculator; };

	virtual ~Fitter() = default;
private:
	Optimizer m_optimizer;
	UncertaintyCalculator m_uncertaintyCalculator;
};


template<class DecoratedOptimizer, class OptimizingType, class SetUpOutput, class AuxilaryParameters>
FittingResults<OptimizingType> Fitter<DecoratedOptimizer, OptimizingType, SetUpOutput, AuxilaryParameters>::fit(
	const OptimizingType& initialParameters, const Data& fittingData, const  AuxilaryParameters& additionalParameters)
{
	typedef SetUpOutput = Optimizer::SetUpOutput; //! we need to fix this, i don't know how (right now)
	SetUpOutput output = m_optimizer.setUpFittingProcedure(initialParameters, fittingData, additionalParameters);
	while (m_optimizer.checkStopCondition())
		m_optimizer.oneStepOfAlgorithm(output);

	if (m_calculateUncertainty)
		std::vector<std::vector<double>> uncertainty = m_uncertaintyCalculator(m_optimizer.getResults());
};

}



