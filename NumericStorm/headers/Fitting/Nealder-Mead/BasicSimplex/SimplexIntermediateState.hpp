#pragma once

#include <vector>

#include "SimplexPoint.hpp"
#include "SimplexFigure.hpp"

namespace NumericStorm::Fitting
{

    template<size_t parameter_size, typename IndeciesEnum, typename OperationEnum>
    struct SimplexIntermediateState
    {
    public:
        using WrappedStateT = void;
    
        SimplexIntermediateState(const SimplexFigure<parameter_size>& simplexFigure, IndeciesEnum pCount)
            : m_simplexFigure{ simplexFigure }, m_intermediatePoints{ pCount, simplexFigure[parameter_size] } {}
    
        
        SimplexFigure& getSimplexFigure() { return m_simplexFigure; }

        std::vector<SimplexPoint>& getAdditionalPoints() { return m_intermediatePoints;}

        const OperationEnum& getCurrentOperation() const { return m_operation; }

        OperationEnum& getCurrentOperation() { return m_operation; }

        const SimplexPoint& getWorstPoint() const { return m_simplexFigure[0]; }

        const SimplexPoint&  getSecondWorstPoint() const { return m_simplexFigure[1]; }

        const SimplexPoint& getBestPoint() const { return m_simplexFigure[parameter_size]; }

        SimplexPoint& getWorstPoint() { return m_simplexFigure[0]; }

        SimplexPoint& getSecondWorstPoint() { return m_simplexFigure[1]; }

        SimplexPoint& getBestPoint() { return m_simplexFigure[parameter_size]; }

        SimplexPoint& operator[](IndeciesEnum index) { return m_intermediatePoints[index]; }

        const SimplexPoint& operator[](IndeciesEnum index) const { return m_intermediatePoints[index]; }

        long int& getIteration() { return m_iteration; }

        const long int& getIteration() const { return m_iteration; }

        WrappedStateT getWrappedState() const {}
    
    protected:
        OperationEnum m_operation{ OperationEnum::Reflection };
        SimplexFigure<parameter_size> m_simplexFigure{};
        std::vector<SimplexPoint<parameter_size>> m_intermediatePoints{};
        long int m_iteration{ 0 };
    };

}