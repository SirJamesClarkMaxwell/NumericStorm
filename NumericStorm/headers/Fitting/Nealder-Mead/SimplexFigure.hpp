#pragma once
#include "Fitting.hpp"


namespace NumericStorm {
namespace Fitting {
template<size_t s_f>
class SimplexFigure {
public:
    SimplexFigure<s_f>() = default;
    SimplexFigure<s_f>() {}; // This constructor needs an implementation
    void sort(bool reverse = true) 
    {
        std::sort(m_points.begin(), m_points.end());
        if (reverse)
            std::reverse(m_points.begin(), m_points.end());
    }
protected:
    std::array<SimplexPoint<s_f - 1>, s_f> m_points;
    SimplexPoint<s_f - 1> m_proposalPoint;
};
}
}