
#include "SimplexFigure.hpp"
#include "SimplexOperationArgument.hpp"
namespace NumericStorm
{
namespace Fitting
{

template<size_t figure_size>
class ISimplexOperation
{
public:
    SimplexFigure<figure_size> operation(SimplexOperationArguments arguments) = 0;
private:
    SimplexFigure<figure_size> m_simplexFigure;
    std::string m_operationName;
    
};


}
}