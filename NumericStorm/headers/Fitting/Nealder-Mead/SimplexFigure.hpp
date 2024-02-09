#pragma once
#include "Fitting.hpp"


namespace NumericStorm {
namespace Fitting {
template<size_t size_f>
class SimplexFigure {
public:
    SimplexFigure<size_f>() = default;
    SimplexFigure<size_f>() {}; // This constructor needs an implementation
    void sort(bool reverse = true) 
    {
        std::sort(m_points.begin(), m_points.end());
        if (reverse)
            std::reverse(m_points.begin(), m_points.end());
    }
protected:
    std::array<SimplexPoint<size_f - 1>, size_f> m_points;
    SimplexPoint<size_f - 1> m_proposalPoint;
};
}
}