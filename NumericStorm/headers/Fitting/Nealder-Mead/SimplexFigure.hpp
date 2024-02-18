#pragma once
#include "SimplexPoint.hpp"
#include <numeric>

namespace NumericStorm {
namespace Fitting {


template<size_t figure_size>
class SimplexFigure {
public:
	SimplexFigure(std::array<SimplexPoint<figure_size - 1>,figure_size> points)
	:m_points(points)
	{m_centroid = calculateCentroid();};
	std::array<SimplexPoint<figure_size - 1>, figure_size> getPoints() { return m_points; }
	void sort(bool reverse = true);
	SimplexPoint<figure_size - 1> getCentroid() { return m_centroid; }
protected:
	std::array<SimplexPoint<figure_size - 1>, figure_size> m_points;
	SimplexPoint<figure_size - 1> m_centroid;
private:
	SimplexPoint<figure_size - 1> calculateCentroid();

};
template<size_t figure_size>
void SimplexFigure<figure_size>::sort(bool reverse) 
{
	std::sort(m_points.begin(), m_points.end());
	if (reverse)
		std::reverse(m_points.begin(), m_points.end());
};

template<size_t figure_size>
SimplexPoint<figure_size - 1> SimplexFigure<figure_size>::calculateCentroid() 
{
	#if DEBUG
		SimplexPoint<figure_size-1> sum = std::accumulate(m_points.begin(), m_points.end(),0);
		SimplexPoint<figure_size -1> toReturn = sum / (figure_size - 1);
		return toReturn;
	#endif
		return std::accumulate(m_points.begin(), m_points.end(), 0) / (figure_size - 1);
}
}
}