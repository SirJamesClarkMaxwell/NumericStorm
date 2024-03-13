#pragma once
#include "../SimplexFigure.hpp"
#include "../SimplexPoint.hpp"

#include "ISimplexFactory.hpp"
#include "../../Exceptions/NoAvailableFactoryException.hpp"
#include "../../Factory.hpp"

namespace NumericStorm 
{
namespace Fitting 
{


template<size_t figure_size>
class SimplexCreatorFactory : public Factory<ISimplexFactory<figure_size>>
{
public:
	SimplexCreatorFactory() = default;
	SimplexCreatorFactory(const SimplexCreatorFactory<figure_size>&) = default;
	SimplexCreatorFactory(SimplexCreatorFactory<figure_size>&&) = default;
	SimplexCreatorFactory<figure_size>& operator=(const SimplexCreatorFactory<figure_size>&) = default;
	SimplexCreatorFactory<figure_size>& operator=(SimplexCreatorFactory<figure_size>&&) = default;

	virtual ~SimplexCreatorFactory() = default;
};


}
}