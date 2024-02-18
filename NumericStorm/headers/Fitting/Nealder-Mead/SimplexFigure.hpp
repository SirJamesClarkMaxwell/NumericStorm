#pragma once
#include "SimplexPoint.hpp"
#include <numeric>

namespace NumericStorm {
namespace Fitting {


template<size_t parameter_size>
class SimplexFigure {
public:
	SimplexFigure() {};
	SimplexFigure( std::array<SimplexPoint<parameter_size>,parameter_size+1> points)
	:m_points(points)
	{m_centroid = calculateCentroid();};
	
	std::array<SimplexPoint<parameter_size >, parameter_size> getPoints() { return m_points; }
	void sort(bool reverse = true);
	SimplexPoint<parameter_size > getCentroid() { return m_centroid; }
protected:
	std::array<SimplexPoint<parameter_size>, parameter_size+1> m_points;
	SimplexPoint<parameter_size> m_centroid;
private:
	SimplexPoint<parameter_size> calculateCentroid();

};
template<size_t parameter_size>
void SimplexFigure<parameter_size>::sort(bool reverse) 
{
	std::sort(m_points.begin(), m_points.end());
	if (reverse)
		std::reverse(m_points.begin(), m_points.end());
};

template<size_t parameter_size>
SimplexPoint<parameter_size> SimplexFigure<parameter_size>::calculateCentroid() 
{
	#if DEBUG
		SimplexPoint<parameter_size> sum = std::accumulate(m_points.begin(), m_points.end(), SimplexPoint<parameter_size>());
		SimplexPoint<parameter_size > toReturn = sum / (parameter_size);
		return toReturn;
	#endif
		return std::accumulate(m_points.begin(), m_points.end(), SimplexPoint<parameter_size>()) / (parameter_size);
}
}
}