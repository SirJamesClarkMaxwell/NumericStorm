#pragma once
#include "FitterSettings.hpp"
#include "Parameters.hpp"
#include <memory>
#include <concepts>

namespace NumericStorm 
{
namespace Fitting 
{
template<size_t parameter_size, class DerivedSettings = FitterSettings<parameter_size>>
class Fitter
{
	//its C++ baby
	//what we are doing here is apparently called "Curiously recurring template pattern"
	//one of the pure virtual functions is defined using the template parameter DerivedSettings
	//then when inheriting from Fitter we specify in its template what kind of settings we want to use

	//here we check the provided class to be inherited from FitterSettings
	static_assert(std::derived_from<DerivedSettings, FitterSettings> == true);

public:
	Fitter() = default;
	Fitter(const Fitter<parameter_size, DerivedSettings>&) = default;
	Fitter(Fitter<parameter_size, DerivedSettings>&&) = default;
	Fitter<parameter_size, DerivedSettings>& operator=(const Fitter<parameter_size, DerivedSettings>&) = default;
	Fitter<parameter_size, DerivedSettings>& operator=(Fitter<parameter_size, DerivedSettings>&&) = default;

	virtual ~Fitter() = default;

	virtual void proposeParameters(const Parameters<parameter_size>& parameters) { m_proposedParameters = parameters; }
	virtual const Parameters<parameter_size>& getFittedParameters() { return m_fittedParamters; }

	virtual void fit() = 0;
	virtual void setUp(const DerivedSettings&) = 0;

protected:
	Parameters<parameter_size> m_fittedParamters{};
	Parameters<parameter_size> m_proposedParameters{};
	std::unique_ptr<DerivedSettings> m_settings{ nullptr };
};

}
}

