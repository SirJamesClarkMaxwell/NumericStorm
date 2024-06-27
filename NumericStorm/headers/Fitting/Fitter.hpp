#pragma once
#include <memory>
#include <concepts>

#include "AdditionalParameters.hpp"
#include "FitterSettings.hpp"
#include "Parameters.hpp"
#include "FittingResults.hpp"

namespace NumericStorm::Fitting {

template<class DecoratedOptimizer, class InitialParameters, class Settings, size_t parameter_size>
concept Optimizer = requires (
	DecoratedOptimizer optimizer, InitialParameters initialParameters,
	AdditionalParameters additionalParameters, Settings settings,
	FittingResults<parameter_size> result
	)
{
	{ optimizer.setUpFittingProcedure(initialParameters, settings) }-> std::convertible_to<void>;
	{ optimizer.checkStopConditions(initialParameters) }-> std::convertible_to<bool>;
	{ optimizer.oneStepAlgorithm(initialParameters, additionalParameters) }-> std::convertible_to<void>;
	{ optimizer.calculateUncertainty(initialParameters) }-> std::convertible_to<void>;
	{ optimizer.getResult() }-> std::convertible_to < FittingResults<parameter_size>>;


};


template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters, class DerivedSettings = FitterSettings<parameter_size, AuxilaryParameters>>
class Fitter
{
	static_assert(std::derived_from<DerivedSettings, FitterSettings<parameter_size, AuxilaryParameters>> == true);

public:
	explicit Fitter(const DerivedSettings& settings, bool calculateUncertainty = true, const Optimizer& optimizer)
		: m_settings{ settings }, m_calculateUncertainty{ calculateUncertainty }, m_optimizer{ optimizer } {};
	FittingResults<parameter_size> fit(
		const Parameters<parameter_size>& initialParameters,
		const AuxilaryParameters& additionalParameters);
	void updateSettings(const DerivedSettings& newSettings) { m_settings = newSettings; };

	virtual ~Fitter() = default;
private:
	Optimizer m_optimizer;
	DerivedSettings m_settings;
	bool m_calculateUncertainty{ true };
};



template<size_t parameter_size, class AuxilaryParameters, class DerivedSettings >
FittingResults<parameter_size> Fitter<parameter_size, AuxilaryParameters, DerivedSettings>::fit(const Parameters<parameter_size>& initialParameters,
	const AuxilaryParameters& additionalParameters)
{
	Parameters<parameter_size> fittingParameters{ initialParameters };
	m_optimizer.setUpFittingProcedure(initialParameters, m_settings);
	while (m_optimizer.checkStopCondition(fittingParameters))
		m_optimizer.oneStepOfAlgorithm(fittingParameters, additionalParameters);

	if m_calculateUncertainty
		m_optimizer.calculateUncertainty(fittingParameters);
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


