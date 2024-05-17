#pragma once

#include "IDecision.hpp"
#include "Factory.hpp"

namespace NumericStorm::Fitting
{
template <size_t parameter_size>
class StrategyManager : public Factory<IDecision<parameter_size>>
{


public:
	StrategyManager() = default;

	virtual ~StrategyManager() = default;

};
}