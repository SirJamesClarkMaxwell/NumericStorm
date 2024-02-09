#pragma once
#include "Fitting.hpp"


namespace NumericStorm {
namespace Fitting {
template<size_t figure_size>
class SimplexFigure {
public:
    SimplexFigure() = default;
    SimplexFigure(std::array<SimplexPoint<figure_size-1>,figure_size> points)
    :m_points(points){};
    void sort(bool reverse = true) 
    {
        std::sort(m_points.begin(), m_points.end());
        if (reverse)
            std::reverse(m_points.begin(), m_points.end());
    }
protected:
    std::array<SimplexPoint<figure_size - 1>, figure_size> m_points;
    SimplexPoint<figure_size - 1> m_proposalPoint;
};
}
}