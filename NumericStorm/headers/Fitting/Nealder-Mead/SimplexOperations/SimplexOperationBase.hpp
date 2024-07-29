#pragma once

#include "VisitorOperationBase.hpp"
#include "SimplexOperationSettings.hpp"

namespace NumericStorm::Fitting
{

template<size_t parameter_size>
class SimplexOperationBase : public VisitorOperationBase<SimplexOperationSettings<parameter_size>>
{
public:
	using enum BasicSimplexIndeciesEnum;
	using SettingsT = typename VisitorOperationBase<SimplexOperationSettings<parameter_size>>::SettingsT;

	SimplexOperationBase() = default;

	SimplexOperationBase(const SettingsT& settings)
		: VisitorOperationBase<SettingsT>{ settings } {}

	virtual ~SimplexOperationBase() = default;

};

}