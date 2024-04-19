#pragma once

#include "IFigureCreator.hpp"
#include "Factory.hpp"

namespace NumericStorm::Fitting
{
template<size_t parameter_size>
class SimplexCreatorFactory : public Factory<IFigureCreator<parameter_size>>
{
public:
	SimplexCreatorFactory() = default;
	SimplexCreatorFactory(const SimplexCreatorFactory<parameter_size>&) = default;
	SimplexCreatorFactory(SimplexCreatorFactory<parameter_size>&&) = default;
	SimplexCreatorFactory<parameter_size>& operator=(const SimplexCreatorFactory<parameter_size>&) = default;
	SimplexCreatorFactory<parameter_size>& operator=(SimplexCreatorFactory<parameter_size>&&) = default;

	virtual ~SimplexCreatorFactory() = default;
};
}