#pragma once
#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"
namespace NumericStorm
{
namespace Fitting
{
template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
struct SimplexIntermediatePoints
{
public:
    SimplexIntermediatePoints() = delete;
    SimplexIntermediatePoints(const SimplexFigure<parameter_size>& simplexFigure)
        :this->simplexFigure{ simplexFigure } {};
    SimplexFigure<parameter_size> simplexFigure{};
    std::vector<SimplexPoint<parameter_size, AuxilaryParameters>> intermediatePoints{};
    SimplexPoint<parameter_size, AuxilaryParameters>& operator[](int index)
    {
        if (index < 0 and index >= intermediatePoints.size())
            throw std::out_of_range("Index out of bounds");
        return intermediatePoints[index];
    }
};

}
}