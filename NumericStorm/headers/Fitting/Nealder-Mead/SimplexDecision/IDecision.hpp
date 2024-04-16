#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "../SimplexFigure.hpp"
#include "../../CreatorInterface.hpp"
#include "StrategySettings.hpp"
namespace NumericStorm
{
namespace Fitting
{

template <size_t parameter_size>
class IDecision : public CreatorInterface<SimplexFigure<parameter_size>&, bool, StrategySettings>
{
public:
	IDecision() = default;
	IDecision(const IDecision<parameter_size>&) = default;
	IDecision(IDecision<parameter_size>&&) = default;
	IDecision<parameter_size>& operator=(const IDecision<parameter_size>&) = default;
	IDecision<parameter_size>& operator=(IDecision<parameter_size>&&) = default;

	virtual ~IDecision() = default;
};

}
}