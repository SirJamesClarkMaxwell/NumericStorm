#pragma once
#include "../SimplexFigure.hpp"
#include "SimplexOperationSettigns.hpp"
#include "../../CreatorInterface.hpp"
#include "SimplexIntermediatePoints.hpp"
namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size>
class ISimplexOperation : public CreatorInterface<SimplexIntermediatePoints<parameter_size, AdditionalParameters>&, void, SimplexOperationSettings>
{

public:

    using InterfaceType = CreatorInterface<SimplexFigure<parameter_size>&, void, SimplexOperationSettings>;
    //Q could we define this alias befor? I am assuming that if you didn't done it we can't
    using In = typename InterfaceType::In;
    using Out = typename InterfaceType::Out;
    using Settings = typename InterfaceType::Settings;

    ISimplexOperation() = default;
    ISimplexOperation(const ISimplexOperation<parameter_size>&) = default;
    ISimplexOperation(ISimplexOperation<parameter_size>&&) = default;
    ISimplexOperation<parameter_size>& operator=(const ISimplexOperation<parameter_size>&) = default;
    ISimplexOperation<parameter_size>& operator=(ISimplexOperation<parameter_size>&&) = default;
    virtual ~ISimplexOperation() = default;

    //NOTE again, i will move this constructor into the beginning of this class
    //todo if we decide to have a general constructor, we should call it here
    ISimplexOperation(const SimplexOperationSettings& arguments)
        : CreatorInterface<In, Out, Settings>{ arguments } {};
    const std::string& getOperationName() const { return m_operationName; }

};

}
}