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
	StrategyManager(const StrategyManager<parameter_size>&) = default;
	StrategyManager(StrategyManager<parameter_size>&&) = default;
	StrategyManager<parameter_size>& operator=(const StrategyManager<parameter_size>&) = default;
	StrategyManager<parameter_size>& operator=(StrategyManager<parameter_size>&&) = default;

	virtual ~StrategyManager() = default;

};
}