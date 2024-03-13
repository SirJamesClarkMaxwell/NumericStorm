#pragma once
#include "SimplexPoint.hpp"
#include <numeric>

namespace NumericStorm {
namespace Fitting {


template<size_t figure_size>
class SimplexFigure {
public:
	SimplexFigure() = default;
	SimplexFigure(const SimplexFigure<figure_size>&) = default;
	SimplexFigure(SimplexFigure<figure_size>&&) = default;
	SimplexFigure<figure_size>& operator=(const SimplexFigure<figure_size>&) = default;
	SimplexFigure<figure_size>& operator=(SimplexFigure<figure_size>&&) = default;

	virtual ~SimplexFigure() = default;

	SimplexFigure(const std::array<SimplexPoint<figure_size-1>, figure_size>& points) {
		//cant be member initializer list because it cant guarantee order of operations
		m_points = points;
		m_centroid = calculateCentroid();
	}
	
	const std::array<SimplexPoint<figure_size-1>, figure_size>& getPoints() const { return m_points; }


	SimplexPoint<figure_size-1>& operator[](int p_index) {
		m_centroid_valid = false;
		m_sorted = false;
		if (p_index >= 0 && static_cast<std::size_t>(p_index) < figure_size)
			return m_points[p_index];
		return m_points[0];
	}

	const SimplexPoint<figure_size - 1>& operator[](int p_index) const {
		if (p_index >= 0 && static_cast<std::size_t>(p_index) < figure_size)
			return m_points[p_index];
		return m_points[0];
	}


	void sort(bool reverse = true) {
		m_sorted = true;
		std::sort(m_points.begin(), m_points.end());
		if (reverse)
			std::reverse(m_points.begin(), m_points.end());
	}


	const SimplexPoint<figure_size-1>&  getCentroid() {
		if (!m_centroid_valid) m_centroid = calculateCentroid();
		return m_centroid; 
	}

	bool isCentroidValid() const { return m_centroid_valid; }
	bool isSorted() const { return m_sorted; }

	SimplexPoint<figure_size-1>& getReflected() { return m_reflected; }
	const SimplexPoint<figure_size-1>& getReflected() { return m_reflected; }

	SimplexPoint<figure_size-1>& getFinal() { return m_final; }
	const SimplexPoint<figure_size-1>& getFinal() { return m_final; }

protected:
	std::array<SimplexPoint<figure_size-1>, figure_size> m_points{};
	SimplexPoint<figure_size-1> m_centroid{};
	SimplexPoint<figure_size-1> m_reflected{};
	SimplexPoint<figure_size-1> m_final{};
	bool m_centroid_valid{ false };
	bool m_sorted{ false };

private:
	SimplexPoint<figure_size-1> calculateCentroid() {
		m_centroid_valid = true;
		if (!m_sorted) sort(); //we must sort because we dont want to include the worst point specifically
	#if DEBUG
		SimplexPoint<figure_size - 1> sum = std::accumulate(++m_points.begin(), m_points.end(), SimplexPoint<figure_size - 1>{});
		sum /= (figure_size - 1);
		return sum;
	#endif
		return std::accumulate(++m_points.begin(), m_points.end(), SimplexPoint<figure_size - 1>()) / (figure_size - 1);
	}

};

}
}