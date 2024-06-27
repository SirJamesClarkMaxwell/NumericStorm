#pragma once
#include <memory>
#include <concepts>

#include "AdditionalParameters.hpp"
#include "FitterSettings.hpp"
#include "Parameters.hpp"
#include "FittingResults.hpp"

namespace NumericStorm::Fitting {

template<class DecoratedOptimizer, class InitialParameters, size_t parameter_size>
concept Optimizer = requires (
	DecoratedOptimizer optimizer, InitialParameters & initialParameters,
	Data & fittingData,
	AdditionalParameters additionalParameters, FittingResults<parameter_size> result
	)
{
	{ optimizer.setUpFittingProcedure(initialParameters, fittingData, additionalParameters) }-> std::convertible_to<void>;
	{ optimizer.checkStopConditions() }-> std::convertible_to<bool>;
	{ optimizer.oneStepAlgorithm() }-> std::convertible_to<void>;
	{ optimizer.calculateUncertainty() }-> std::convertible_to<void>;
	{ optimizer.getResult() }-> std::convertible_to < FittingResults<parameter_size>>;


};


template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters, class DerivedSettings >
class Fitter
{
public:
	explicit Fitter(const DerivedSettings& settings, bool calculateUncertainty = true, const Optimizer& optimizer)
		: m_settings{ settings }, m_calculateUncertainty{ calculateUncertainty }, m_optimizer{ optimizer } {};

	FittingResults<parameter_size> fit(const Parameters<parameter_size>& initialParameters, const Data& fittingData,
		const AuxilaryParameters& additionalParameters);


	void updateSettings(const DerivedSettings& newSettings) { m_settings = newSettings; };

	virtual ~Fitter() = default;
private:
	DerivedSettings m_settings;
	bool m_calculateUncertainty{ true };
	Optimizer m_optimizer;
};



template<size_t parameter_size, class AuxilaryParameters, class DerivedSettings >
FittingResults<parameter_size> Fitter<parameter_size, AuxilaryParameters, DerivedSettings>::fit(
	const Parameters<parameter_size>& initialParameters, const Data& fittingData, const  AuxilaryParameters& additionalParameters)
{

	m_optimizer.setUpFittingProcedure(initialParameters, fittingData, additionalParameters);
	while (m_optimizer.checkStopCondition())
		m_optimizer.oneStepOfAlgorithm();

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


