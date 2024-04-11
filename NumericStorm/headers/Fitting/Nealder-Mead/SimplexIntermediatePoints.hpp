#pragma once
#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"
namespace NumericStorm
{
namespace Fitting
{
//rename to SimplexState
template<size_t parameter_size>
struct SimplexIntermediatePoints
{
public:
    SimplexIntermediatePoints() = delete;
    SimplexIntermediatePoints(const SimplexFigure<parameter_size>& simplexFigure)
        : this->simplexFigure{ simplexFigure } {};
    SimplexFigure<parameter_size> simplexFigure{};
    std::vector<SimplexPoint<parameter_size>> intermediatePoints{};


    SimplexPoint<parameter_size>& operator[](int index) return intermediatePoints.at(index);
    const SimplexPoint<parameter_size>& operator[](int index) const return intermediatePoints.at(index);
};

}
}