#pragma once
#include <memory>
#include <concepts>

#include "AdditionalParameters.hpp"
#include "FitterSettings.hpp"
#include "Parameters.hpp"


namespace NumericStorm::Fitting {

template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters, class DerivedSettings = FitterSettings<parameter_size, AuxilaryParameters>>
class Fitter
{
	static_assert(std::derived_from<DerivedSettings, FitterSettings<parameter_size, AuxilaryParameters>> == true);

public:
	Fitter() = delete;
	Fitter(const DerivedSettings& settings)
		:m_settings{ settings } {};
	Fitter(const Fitter<parameter_size, AuxilaryParameters, DerivedSettings>&) = default;
	Fitter(Fitter<parameter_size, AuxilaryParameters, DerivedSettings>&&) = default;
	Fitter<parameter_size, AuxilaryParameters, DerivedSettings>& operator=(const Fitter<parameter_size, AuxilaryParameters, DerivedSettings>&) = default;
	Fitter<parameter_size, AuxilaryParameters, DerivedSettings>& operator=(Fitter<parameter_size, AuxilaryParameters, DerivedSettings>&&) = default;

	virtual ~Fitter() = default;
	virtual Parameters<parameter_size> fit(
		const Parameters<parameter_size>& initialParameters,
		const AuxilaryParameters& additionalParameters) = 0;
	void updateSettings(const DerivedSettings& newSettings) { m_settings = newSettings; };
	virtual void setUp() = 0;
protected:
	DerivedSettings m_settings;
};

}
