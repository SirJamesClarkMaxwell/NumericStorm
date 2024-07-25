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
    
        
        auto& getSimplexFigure() { return m_simplexFigure; }

        std::vector<SimplexPoint<parameter_size>>& getAdditionalPoints() { return m_intermediatePoints;}

        const OperationEnum& getCurrentOperation() const { return m_operation; }

        OperationEnum& getCurrentOperation() { return m_operation; }

        const auto& getWorstPoint() const { return m_simplexFigure[0]; }

        const auto&  getSecondWorstPoint() const { return m_simplexFigure[1]; }

        const auto& getBestPoint() const { return m_simplexFigure[parameter_size]; }

        auto& getWorstPoint() { return m_simplexFigure[0]; }

        auto& getSecondWorstPoint() { return m_simplexFigure[1]; }

        auto& getBestPoint() { return m_simplexFigure[parameter_size]; }

        auto& operator[](IndeciesEnum index) { return m_intermediatePoints[index]; }

        const auto& operator[](IndeciesEnum index) const { return m_intermediatePoints[index]; }

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