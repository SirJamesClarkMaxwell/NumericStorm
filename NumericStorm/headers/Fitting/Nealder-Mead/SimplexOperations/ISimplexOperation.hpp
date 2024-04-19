#pragma once
#include "../SimplexFigure.hpp"
#include "SimplexOperationSettigns.hpp"
#include "../../CreatorInterface.hpp"
#include "../PIndecies.hpp"
#include "SimplexIntermediatePoints.hpp"

namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size>
class ISimplexOperation : public CreatorInterface<SimplexIntermediatePoints<parameter_size>&, void, SimplexOperationSettings>
{
public:

    using InterfaceType = CreatorInterface<SimplexIntermediatePoints<parameter_size>&, void, SimplexOperationSettings>;
    using In = typename InterfaceType::In;
    using Out = typename InterfaceType::Out;
    using Settings = typename InterfaceType::Settings;
    using enum PIndicies;
    using enum SimplexFigure<parameter_size>::SimplexFigureIndicies;

    ISimplexOperation(const std::string& name, const SimplexOperationSettings& settings)
        : CreatorInterface<In, Out, Settings>{ settings }, m_operationName{ name } {};
    ISimplexOperation() = default;
    ISimplexOperation(const ISimplexOperation<parameter_size>&) = default;
    ISimplexOperation(ISimplexOperation<parameter_size>&&) = default;
    ISimplexOperation<parameter_size>& operator=(const ISimplexOperation<parameter_size>&) = default;
    ISimplexOperation<parameter_size>& operator=(ISimplexOperation<parameter_size>&&) = default;
    virtual ~ISimplexOperation() = default;
    virtual const std::string& getOperationName() const { return m_operationName; }
protected:
    std::string m_operationName{};
};

}
}