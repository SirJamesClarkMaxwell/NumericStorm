#pragma once
#include "ISimplexOperation.hpp"
#include "Factory.hpp"

namespace NumericStorm:: Fitting
{
template <size_t parameter_size>
class SimplexOperationFactory : public Factory<ISimplexOperation<parameter_size>>
{
public:
	SimplexOperationFactory() = default;
	SimplexOperationFactory(const SimplexOperationFactory<parameter_size>&) = default;
	SimplexOperationFactory(SimplexOperationFactory<parameter_size>&&) = default;
	SimplexOperationFactory<parameter_size>& operator=(const SimplexOperationFactory<parameter_size>&) = default;
	SimplexOperationFactory<parameter_size>& operator=(SimplexOperationFactory<parameter_size>&&) = default;

	virtual ~SimplexOperationFactory() = default;

};
}