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
    ISimplexOperation(const std::string& name, const SimplexFigure<figure_size>& simplexFigure)
        :m_operationName(name), m_simplexFigure(simplexFigure){};
    //virtual SimplexFigure<figure_size> operation(const SimplexOperationArguments& arguments) = 0;
    virtual SimplexFigure<figure_size>operator ()(const SimplexOperationArguments& arguments) = 0;
protected:
    SimplexFigure<figure_size> m_simplexFigure;
    std::string m_operationName;
    
};


}
}