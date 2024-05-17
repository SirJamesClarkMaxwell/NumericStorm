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

	virtual ~SimplexCreatorFactory() = default;
};
}