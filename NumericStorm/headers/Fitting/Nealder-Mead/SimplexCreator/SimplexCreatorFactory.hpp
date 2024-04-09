#pragma once
#include "../SimplexFigure.hpp"
#include "../SimplexPoint.hpp"

#include "IFigureCreator.hpp"
#include "../../Exceptions/NoAvailableFactoryException.hpp"
#include "../../Factory.hpp"

namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size>
class SimplexCreatorFactory : public Factory<ISimplexFactory<parameter_size>>
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
}