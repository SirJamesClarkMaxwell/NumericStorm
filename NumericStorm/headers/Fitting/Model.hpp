#pragma once

#include "Fitting.hpp"

namespace NumericStorm 
{
namespace Fitting 
{
template <size_t size_p>
class Model
{
public:
	Model() = default;
	Model() {}
	virtual Data& operator (const Parameters<size_p>& parameters,
		const AdditionalParameters& additionalParameters) = 0;
protected:
	std::function< Data& (const Parameters<size_p>& parameters,
		const AdditionalParameters& additionalParameters) m_model;

};
}
}