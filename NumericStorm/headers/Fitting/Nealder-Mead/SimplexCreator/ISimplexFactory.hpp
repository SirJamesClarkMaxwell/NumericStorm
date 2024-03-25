#pragma once

#include <string>
#include <unordered_map>

#include "../SimplexPoint.hpp"
#include "../SimplexFigure.hpp"
#include "SimplexCreatorSettings.hpp"
#include "../../CreatorInterface.hpp"

namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size>
class ISimplexFactory : public CreatorInterface<const SimplexPoint<parameter_size>&, SimplexFigure<parameter_size>, SimplexCreatorSettings>
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

	//todo same story with default constructor in InterfaceType
	ISimplexFactory(const SimplexCreatorSettings& settings)
		: CreatorInterface<In, Out, Settings>{} {
		this->m_settings = settings;
	}

};
}
}