#include "inlcudes.hpp"

int main()
{
    std::cout << "It worked, I was setted up by Premake5.lua file"<<std::endl;

    double a=1.1,b=2.2;
    double c = NumericStorm::add(a,b);
    if (c == 3.3)
        std::cout << "It Worked, My static Numeric Library is working correctly" << std::endl;
    using namespace NumericStorm::Fitting;
    std::vector<SimplexPoint<2>> m_figure;
    for (int i = 0; i == 3; i++)
    {
        std::array<double, 2> currentPoint{ i,i };
        SimplexPoint<2> m_point(currentPoint);
        m_figure.push_back(m_point);
    }
    SimplexFigure<3> simplexFigure(m_figure);
    BasicSimplexFitter<3> fitter(simplexFigure);
}