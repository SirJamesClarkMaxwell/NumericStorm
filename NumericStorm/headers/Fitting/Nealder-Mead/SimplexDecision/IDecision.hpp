#pragma once
#include "SimplexFigure.hpp"
#include "CreatorInterface.hpp"
#include "StrategySettings.hpp"
#include "SimplexIntermediatePoints.hpp"
#include "PIndices.hpp"


namespace NumericStorm::Fitting
{

template <size_t parameter_size>
class IDecision : public CreatorInterface<SimplexIntermediatePoints<parameter_size>&, bool, StrategySettings>
{
public:
	using InterfaceType = typename CreatorInterface<SimplexIntermediatePoints<parameter_size>&, bool, StrategySettings>;
	using In = typename InterfaceType::In;
	using Out = typename InterfaceType::Out;
	using Settings = typename InterfaceType::Settings;
	using enum PIndices;
	using enum SimplexFigureIndicies;
	static const int bestPoint = SimplexFigure<parameter_size>::bestPoint;

	IDecision() = default;
	IDecision(const IDecision<parameter_size>&) = default;
	IDecision(IDecision<parameter_size>&&) = default;
	IDecision<parameter_size>& operator=(const IDecision<parameter_size>&) = default;
	IDecision<parameter_size>& operator=(IDecision<parameter_size>&&) = default;

	IDecision(const StrategySettings& settings) : CreatorInterface<In, Out, Settings>{ settings } {}

	virtual ~IDecision() = default;
};
}