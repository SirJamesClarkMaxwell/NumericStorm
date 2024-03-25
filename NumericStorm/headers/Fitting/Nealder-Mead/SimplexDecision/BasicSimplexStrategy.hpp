#include "IDecision.hpp"
#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"

namespace NumericStorm
{
namespace Fitting
{
enum SimplexOperationType
{
    OldSimplex,
    Reflection,
    Expansion,
    Contraction,
    Shrinking
};
enum GreedyApproach
{
    minimization,
    expansion
};
template <size_t parameter_size>
class BasicSimplexDecision : public IDecision<parameter_size>
{
public:
    BasicSimplexDecision(int greedyApproach)
        :m_greedyApproach(greedyApproach) {};
    virtual ~BasicSimplexDecision();
    virtual SimplexFigure<parameter_size> makeDecision(const std::vector<SimplexFigure<parameter_size>>& simplexFigures) override;
    void checkDimensionsOfVector(const std::vector<SimplexFigure<parameter_size>>& simplexFigures) const throw(std::out_of_range);
private:
    int m_greedyApproach;
    int checkReflectionCondition(const SimplexPoint<parameter_size>& bestPointOldSimplex, const SimplexPoint<parameter_size>& reflectedPoint, const SimplexPoint<parameter_size>& expandedPoint, const SimplexPoint<parameter_size>& secondBestPointOldSimplex);
    int checkReflectionCondition(const SimplexPoint<parameter_size>& contractedPoint, const SimplexPoint<parameter_size>& reflectedPoint, const SimplexPoint<parameter_size>& worstOldPoint);
};
template <size_t parameter_size>
SimplexFigure<parameter_size> BasicSimplexDecision<parameter_size>::makeDecision(const std::vector<SimplexFigure<parameter_size>>& simplexFigures)
{
    this->checkDimensionsOfVector(simplexFigures.size());
    SimplexPoint<parameter_size> bestPointOldSimplex = simplexFigures[OldSimplex][0];
    SimplexPoint<parameter_size> secondBestPointOldSimplex = simplexFigures[OldSimplex][1];
    SimplexPoint<parameter_size> worstOldPoint = simplexFigures[OldSimplex][parameter_size];

    SimplexPoint<parameter_size> expandedPoint = simplexFigures[Expansion][0];
    SimplexPoint<parameter_size> reflectedPoint = simplexFigures[Reflection][0];
    SimplexPoint<parameter_size> contractedPoint = simplexFigures[Contraction][0];

    //FIXME the code of below functions looks like a total mess, but i have no other idea
    int chosenOption = checkReflectionCondition(bestPointOldSimplex, reflectedPoint, expandedPoint, secondBestPointOldSimplex);
    // FIXME: the name of this variable could be changed! if you have a better name, please let change it!
    if (chosenOption == Contraction)
        chosenOption = checkShrinkingCondition(bestPointOldSimplex, contractedPoint, reflectedPoint, worstOldPoint);

    return simplexFigures[chosenOption];

}
template <size_t parameter_size>
void BasicSimplexDecision<parameter_size>::checkDimensionsOfVector(const int sizeOfVector) const throw(std::out_of_range)
{
    if (!(simplexFigures.size() == Shrinking + 1))
    {
        throw std::out_of_range("The number of simplex figures must be" + std::to_string(Shrinking + 1) + "!");
    }
}
template <size_t parameter_size>
int BasicSimplexDecision<parameter_size>::checkReflectionCondition(
    const SimplexPoint<parameter_size>& bestPointOldSimplex, const SimplexPoint<parameter_size>& reflectedPoint,
    const SimplexPoint<parameter_size>& expandedPoint, const SimplexPoint<parameter_size>& secondBestPointOldSimplex)
{
    if ((bestPointOldSimplex <= reflectedPoint) and (reflectedPoint <= secondBestPointOldSimplex))
    {
        if ((m_greedyApproach == minimization) and (expandedPoint < reflectedPoint) and (reflectedPoint < bestPointOldSimplex))
            return Expansion;
        else if ((expandedPoint < secondBestPointOldSimplex) and (reflectedPoint < bestPointOldSimplex))
            return Expansion;
        else
            return Reflection;
    }
    else
        return Contraction;
};
template <size_t parameter_size>
int BasicSimplexDecision<parameter_size>::checkShrinkingCondition(
    const SimplexPoint<parameter_size>& bestOldPoint, const SimplexPoint<parameter_size>& contractedPoint,
    const SimplexPoint<parameter_size>& reflectedPoint, const SimplexPoint<parameter_size>& worstOldPoint)
{
    //FIXME this code looks horrible, but i have no other idea
    if (reflectedPoint < bestPointOldSimplex)
    {
        if (contractedPoint <= reflectedPoint)
            return Contraction;
        else
            return Shrinking;
    }
    else
    {
        if (contractedPoint <= worstOldPoint)
            return Contraction;
        else
            return Contraction;
    }
}
}