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
	static_assert(std::derived_from<DerivedSettings, FitterSettings> == true);

public:
	Fitter() = default;
	Fitter(const Fitter<parameter_size, DerivedSettings>&) = default;
	Fitter(Fitter<parameter_size, DerivedSettings>&&) = default;
	Fitter<parameter_size, DerivedSettings>& operator=(const Fitter<parameter_size, DerivedSettings>&) = default;
	Fitter<parameter_size, DerivedSettings>& operator=(Fitter<parameter_size, DerivedSettings>&&) = default;

	virtual ~Fitter() = default;
	virtual Parameters<parameter_size> fit(const Parameters<parameter_size>& initialParameters) = 0;
	virtual void setUp(const DerivedSettings&) = 0;

protected:
	std::unique_ptr<DerivedSettings> m_settings{ nullptr };
};

}
}

