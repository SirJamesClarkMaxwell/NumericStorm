#pragma once

#include <vector>

#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"
namespace NumericStorm::Fitting
{
//rename to SimplexState
template<size_t parameter_size>
struct SimplexIntermediatePoints
{
public:
    SimplexIntermediatePoints() = delete;
    template<typename IndeciesEnum>
    SimplexIntermediatePoints(const SimplexFigure<parameter_size>& simplexFigure, IndeciesEnum pCount)
        : m_simplexFigure{ simplexFigure }, m_intermediatePoints{ pCount, simplexFigure[SimplexFigureIndicies::worstPoint] } {}

    SimplexFigure<parameter_size> m_simplexFigure{};
    std::vector<SimplexPoint<parameter_size>> m_intermediatePoints;

    template<typename IndeciesEnum>
    SimplexPoint<parameter_size>& operator[](IndeciesEnum index) { return m_intermediatePoints.at(index); }

    template<typename IndeciesEnum>
    const SimplexPoint<parameter_size>& operator[](IndeciesEnum index) const { return m_intermediatePoints.at(index); }
};

}