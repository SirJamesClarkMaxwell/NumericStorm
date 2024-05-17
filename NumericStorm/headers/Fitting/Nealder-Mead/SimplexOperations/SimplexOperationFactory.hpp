#pragma once
#include "ISimplexOperation.hpp"
#include "Factory.hpp"

namespace NumericStorm::Fitting
{
template <size_t parameter_size>
class SimplexOperationFactory : public Factory<ISimplexOperation<parameter_size>>
{
public:
	SimplexOperationFactory() = default;

	virtual ~SimplexOperationFactory() = default;

};
}