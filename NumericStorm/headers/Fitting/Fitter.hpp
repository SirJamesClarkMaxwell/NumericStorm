#pragma once
#include <memory>
#include <concepts>

#include "AdditionalParameters.hpp"
#include "FitterSettings.hpp"
#include "Parameters.hpp"


namespace NumericStorm::Fitting {
template<size_t parameters_size>
struct FittingResults
{
public:
	FittingResults(const Parameters<parameters_size> parameters, size_t iterationCounts, double minimalError)
		:m_parameters{ parameters }, m_iterationCounts{ iterationCounts }, m_minimum_error{ minimalError } {}
	Parameters<parameters_size> m_parameters{};
	size_t m_iterationCounts{ 0 };
	double m_minimum_error{ -1 };
	std::array<std::array<double, parameters_size>, parameters_size> m_covariance_matrix{};

};

template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters, class DerivedSettings = FitterSettings<parameter_size, AuxilaryParameters>>
class Fitter
{
	static_assert(std::derived_from<DerivedSettings, FitterSettings<parameter_size, AuxilaryParameters>> == true);

public:
	explicit Fitter(const DerivedSettings& settings, bool calculateUncertainty = true)
		: m_settings{ settings }, m_calculateUncertainty{ calculateUncertainty } {};
	virtual FittingResults<parameter_size> fit(
		const Parameters<parameter_size>& initialParameters,
		const AuxilaryParameters& additionalParameters) = 0;
	virtual void setUp() = 0;
	void updateSettings(const DerivedSettings& newSettings) { m_settings = newSettings; };
	/*
		Fitter(const Fitter<parameter_size, AuxilaryParameters, DerivedSettings>&) = default;
		Fitter(Fitter<parameter_size, AuxilaryParameters, DerivedSettings>&&) = default;
		Fitter<parameter_size, AuxilaryParameters, DerivedSettings>& operator=(const Fitter<parameter_size, AuxilaryParameters, DerivedSettings>&) = default;
		Fitter<parameter_size, AuxilaryParameters, DerivedSettings>& operator=(Fitter<parameter_size, AuxilaryParameters, DerivedSettings>&&) = default;
	*/

	virtual ~Fitter() = default;
protected:
	DerivedSettings m_settings;
	bool m_calculateUncertainty{ true };
};

}
