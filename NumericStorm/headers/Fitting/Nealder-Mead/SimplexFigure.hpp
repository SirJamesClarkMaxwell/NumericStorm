#pragma once
#include "SimplexPoint.hpp"
#include <numeric>

namespace NumericStorm {
namespace Fitting {


template<size_t parameter_size>
class SimplexFigure {
public:
	SimplexFigure() {};
	SimplexFigure(std::array<SimplexPoint<parameter_size>, parameter_size + 1> points, const std::shared_ptr<Data>& referenceData)
		:m_points(points), m_centroid(calculateCentroid()), m_referencedData{ referenceData };

	std::array<SimplexPoint<parameter_size >, parameter_size> getPoints() { return m_points; }
	void sort(bool reverse = true);
	SimplexPoint<parameter_size>& getCentroid() { return m_centroid; }
	SimplexPoint<parameter_size>& operator[](unsigned int index);
	const SimplexPoint<parameter_size>& operator[](unsigned int index) const;
	void recalculateErrors();
	void recalculateError(unsigned int index);

protected:
	std::array<SimplexPoint<parameter_size>, parameter_size + 1> m_points;
	SimplexPoint<parameter_size> m_centroid;

private:
	SimplexPoint<parameter_size> calculateCentroid();
	std::shared_ptr<Data> m_referencedData;

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
	SimplexPoint<parameter_size> sum = std::accumulate(m_points.begin() + 1, m_points.end(), m_points[0]);
	SimplexPoint<parameter_size > toReturn = sum / (parameter_size);
	return toReturn;
#endif
	return std::accumulate((m_points.begin() + 1), m_points.end(), m_points[0]) / (parameter_size);
};

template<size_t parameter_size>
SimplexPoint<parameter_size>& SimplexFigure<parameter_size>::operator[](unsigned int index) {
	if (index >= parameter_size + 1) {
		throw std::out_of_range("Index out of bounds");
	}
	return m_points[index];
};

template<size_t parameter_size>
const SimplexPoint<parameter_size>& SimplexFigure<parameter_size>::operator[](unsigned int index) const {
	if (index >= parameter_size + 1) {
		throw std::out_of_range("Index out of bounds");
	}
	return m_points[index];
}

template<size_t parameter_size>
void SimplexFigure<parameter_size>::recalculateErrors()
{
	for (auto& point : m_points)
		point.calculateError(m_referencedData);
};
template<size_t parameter_size>
void SimplexFigure<parameter_size>::recalculateError(unsigned int index)
{
	if (index >= parameter_size)
		throw std::out_of_range("Index out of bounds");
	m_points[index].calculateError(m_referencedData);
};
}