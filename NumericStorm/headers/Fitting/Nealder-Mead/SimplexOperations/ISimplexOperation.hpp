#pragma once
#include "../SimplexFigure.hpp"
#include "SimplexOperationSettigns.hpp"
namespace NumericStorm
{
namespace Fitting
{

template<size_t parameter_size>
class ISimplexOperation
{
private:
    ISimplexOperation(const std::string& name, const SimplexOperationSettigns& arguments)
        :m_operationName(name), m_settings(arguments){};

public:
    virtual SimplexFigure<parameter_size>operator ()(const SimplexFigure<parameter_size>&simplexFigure) = 0;
    void updateSettigns(const SimplexOperationSettigns& newArguments);
protected:
    SimplexOperationSettigns m_settings;
    std::string m_operationName;
    
};


}
}