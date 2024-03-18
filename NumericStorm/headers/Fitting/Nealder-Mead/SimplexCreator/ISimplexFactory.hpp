#pragma once

#include <string>
#include <unordered_map>

#include "../SimplexPoint.hpp"
#include "../SimplexFigure.hpp"
#include "SimplexCreatorSetting.hpp"
#include "../../CreatorInterface.hpp"

namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size>
class ISimplexFactory : public CreatorInterface<SimplexPoint<parameter_size>, SimplexFigure<parameter_size>, SimplexCreatorSettigns>
{
public:
	using InterfaceType = CreatorInterface<SimplexFigure<parameter_size>&, SimplexFigure<parameter_size>&, SimplexOperationSettings>;
	using In = typename InterfaceType::In;
	using Out = typename InterfaceType::Out;
	using Settings = typename InterfaceType::Settings;

	ISimplexFactory() = default;
	ISimplexFactory(const ISimplexFactory&) = default;
	ISimplexFactory(ISimplexFactory&&) = default;
	ISimplexFactory& operator=(const ISimplexFactory&) = default;
	ISimplexFactory& operator=(ISimplexFactory&&) = default;

	virtual ~ISimplexFactory() = default;

	ISimplexFactory(SimplexCreatorSettigns settings)
		: CreatorInterface<In, Out, Settings>{}  {
		this->m_settings = settings;
	}

};
}
}