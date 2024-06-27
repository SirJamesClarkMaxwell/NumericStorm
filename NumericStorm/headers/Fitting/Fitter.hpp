#pragma once
#include <memory>
#include <concepts>

#include "AdditionalParameters.hpp"
#include "OptimizerSettings.hpp"
#include "Parameters.hpp"
#include "FittingResults.hpp"

namespace NumericStorm::Fitting {

template<class DecoratedOptimizer, class InitialParameters, size_t parameter_size, class SetUpOutput>
concept Optimizer = requires (
	DecoratedOptimizer optimizer, InitialParameters & initialParameters,
	Data & fittingData,
	AdditionalParameters additionalParameters, FittingResults<parameter_size> result,
	SetUpOutput output
	)
{
	{ optimizer.setUpFittingProcedure(initialParameters, fittingData, additionalParameters) }-> std::convertible_to<SetUpOutput>;
	{ optimizer.checkStopConditions() }-> std::convertible_to<bool>;
	{ optimizer.oneStepAlgorithm(output) }-> std::convertible_to<void>;
	{ optimizer.calculateUncertainty() }-> std::convertible_to<void>;
	{ optimizer.getResult() }-> std::convertible_to < FittingResults<parameter_size>>;


};


template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters >
class Fitter
{
public:
	explicit Fitter(const Optimizer& optimizer, bool calculateUncertainty = true)
		: m_optimizer{ optimizer }, m_calculateUncertainty{ calculateUncertainty } {};

	FittingResults<parameter_size> fit(const Parameters<parameter_size>& initialParameters, const Data& fittingData,
		const AuxilaryParameters& additionalParameters);

	virtual ~Fitter() = default;
private:

	Optimizer m_optimizer;
};



template<size_t parameter_size, class AuxilaryParameters>
FittingResults<parameter_size> Fitter<parameter_size, AuxilaryParameters>::fit(
	const Parameters<parameter_size>& initialParameters, const Data& fittingData, const  AuxilaryParameters& additionalParameters)
{
	typedef SetUpOutput = Optimizer::SetUpOutput; //! we need to fix this, i don't know how (right now)
	SetUpOutput output = m_optimizer.setUpFittingProcedure(initialParameters, fittingData, additionalParameters);
	while (m_optimizer.checkStopCondition())
		m_optimizer.oneStepOfAlgorithm(output);

	if m_calculateUncertainty
		m_optimizer.calculateUncertainty();
#if DEBUG
	FittingResults<parameter_size> results = m_optimizer.getResults();
	return results
#else
	return m_optimizer.getResults();
#endif

};
}
//! STEPS of refactoring

//NOTE Optimizer has to have a tables of 

//TODO add concepts
	//TODO oneStepOfAlgorithm
	//TODO checkStopCondition
	//TODO setUp
	//TODO setUpFittingProcedure

//TODO change the name of Fitting -> Optimizer
//TODO add Fitting class and the most general fitting algorithm
//TODO remove inheritance 


