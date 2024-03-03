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
        template <size_t parameter_size>
        class BasicSimplexDecision : public IDecision<parameter_size>
        {
        public:
            BasicSimplexDecision();
            virtual ~BasicSimplexDecision();
            virtual SimplexFigure<parameter_size>(const std::vector<SimplexFigure<parameter_size>> &simplexFigures) override;
            void checkDimensionsOfVector(const std::vector<SimplexFigure<parameter_size>> &simplexFigures) const throw(std::out_of_range);
        };
        template <size_t parameter_size>
        SimplexFigure<parameter_size> BasicSimplexDecision<parameter_size>::makeDecision(const std::vector<SimplexFigure<parameter_size>> &simplexFigures)
        {
            SimplexFigure<parameter_size> toReturn;
            SimplexPoint<parameter_size> bestPointOldSimplex = simplexFigures[OldSimplex][0];
            SimplexPoint<parameter_size> reflectedPoint = simplexFigures[Reflection][0];
            SimplexPoint<parameter_size> expandedPoint = simplexFigures[Expansion][0];
            SimplexPoint<parameter_size> contractedPoint = simplexFigures[Contraction][0];
            if ((reflectedPoint < bestPointOldSimplex) and (reflectedPoint > simplexFigures[OldSimplex][parameter_size - 2]))
                toReturn = simplexFigures[Reflection];
            else if (expandedPoint < bestPointOldSimplex)
                toReturn = simplexFigures[Expansion];
            else if (contractedPoint < simplexFigures[OldSimplex][1])
                toReturn = simplexFigures[complicatedSimplex];
            else
                toReturn = simplexFigures[Shrinking];

            return toReturn;
        }
        template <size_t parameter_size>
        void BasicSimplexDecision<parameter_size>::checkDimensionsOfVector(const std::vector<SimplexFigure<parameter_size>> &simplexFigures) const throw(std::out_of_range)
        {
            if (simplexFigures.size() != Shrinking + 1)
            {
                throw std::out_of_range("The number of simplex figures must be" + std::to_string(Shrinking + 1) + "!");
            }
        }
    }

}