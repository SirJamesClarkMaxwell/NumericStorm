#pragma once
#include "../SimplexFigure.hpp"
#include "SimplexOperationArguments.hpp"
namespace NumericStorm
{
namespace Fitting
{

template<size_t figure_size>
class ISimplexOperation
{
public:
    ISimplexOperation(const std::string& name, const SimplexOperationArguments& arguments)
        :m_operationName(name), m_arguments(arguments){};

    virtual SimplexFigure<figure_size>operator ()() = 0;
protected:
    SimplexOperationArguments m_arguments;
    std::string m_operationName;
    
};


}
}