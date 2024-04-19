#pragma once
#include "SimplexPoint.hpp"
#include "../Exceptions/NoSetDataException.hpp"
#include <numeric>

namespace NumericStorm {
namespace Fitting {


template<size_t parameter_size>
class SimplexFigure {
public:
	SimplexFigure(const std::array<SimplexPoint<parameter_size>, parameter_size + 1>& points)
		: m_points{ points }, m_centroid{ calculateCentroid() } {}
	enum SimplexFigureIndicies
	{
		worstPoint = 0,
		secondWorstPoint = 1,
		bestPoint = parameter_size

	};
	SimplexFigure() = delete;
	SimplexFigure(const SimplexFigure<parameter_size>&) = default;
	SimplexFigure(SimplexFigure<parameter_size>&&) = default;
	SimplexFigure<parameter_size>& operator=(const SimplexFigure<parameter_size>&) = default;
	SimplexFigure<parameter_size>& operator=(SimplexFigure<parameter_size>&&) = default;
	virtual ~SimplexFigure() = default;
	const std::array<SimplexPoint<parameter_size>, parameter_size + 1>& getPoints() const { return m_points; }
	SimplexPoint<parameter_size>& operator[](int p_index) {
		m_centroid_valid = false;
		m_sorted = false;
		return m_points.at(p_index);
	}

	const SimplexPoint<parameter_size>& operator[](int p_index) const {
		return m_points.at(p_index);
	}


	void sort(bool reverse = true) {
		m_sorted = true;
		std::sort(m_points.begin(), m_points.end());
		if (reverse)
			std::reverse(m_points.begin(), m_points.end());
	}


	const SimplexPoint<parameter_size>& getCentroid() {
		if (!m_centroid_valid) m_centroid = calculateCentroid();
		return m_centroid;
	}

	bool isCentroidValid() const { return m_centroid_valid; }
	bool isSorted() const { return m_sorted; }


protected:
	std::array<SimplexPoint<parameter_size>, parameter_size + 1> m_points{};
	SimplexPoint<parameter_size> m_centroid{};
	bool m_centroid_valid{ false };
	bool m_sorted{ false };

private:
	SimplexPoint<parameter_size> calculateCentroid() {
		m_centroid_valid = true;
		if (!m_sorted) sort(false);
#if DEBUG
		SimplexPoint<parameter_size> sum = std::accumulate(++m_points.begin(), m_points.end(), SimplexPoint<parameter_size>{});
		sum /= (parameter_size);
		return sum;
#endif
		return std::accumulate(++m_points.begin(), m_points.end(), SimplexPoint<parameter_size>()) / (parameter_size);
	}

};

}
}