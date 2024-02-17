#include "inlcudes.hpp"

int main()
{
    std::cout << "It worked, I was setted up by Premake5.lua file"<<std::endl;

    double a=1.1,b=2.2;
    double c = NumericStorm::add(a,b);
    if (c == 3.3)
        std::cout << "It Worked, My static Numeric Library is working correctly" << std::endl;
    using namespace NumericStorm::Fitting;
    AdditionalParameters additional;
    std::array<SimplexPoint<2>,3> m_figure;
    for (int i = 0; i == 2; i++)
    {
        std::array<double, 2> currentPoint{ i,i };
        SimplexPoint<2> m_point(currentPoint,additional);
        m_figure[i]=m_point;
    }
    std::array<SimplexPoint<2>, 3> figure = m_figure;
    SimplexFigure<2> simplexFigure = SimplexFigure<2>(m_figure);   //(m_figure);
    BasicSimplexFitter<2> fitter(simplexFigure);
}