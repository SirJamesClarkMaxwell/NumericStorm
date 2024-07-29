#pragma once

#include <numeric>
#include <array>
#include <algorithm>

#include "SimplexPoint.hpp"


namespace NumericStorm::Fitting {


template<size_t parameter_size>
class SimplexFigure {
public:

	SimplexFigure(const std::array<SimplexPoint<parameter_size>, parameter_size + 1>& points)
		: m_points{ points }, m_centroid{ calculateCentroid() } {}


	virtual ~SimplexFigure() = default;

	const std::array<SimplexPoint<parameter_size>, parameter_size + 1>& getPoints() const { return m_points; }
	std::array<SimplexPoint<parameter_size>, parameter_size + 1>& getPoints() { return m_points; }

	SimplexPoint<parameter_size>& operator[](size_t p_index) {
		m_centroid_valid = false;
		m_sorted = false;
		return m_points.at(p_index);
	}

	const SimplexPoint<parameter_size>& operator[](size_t p_index) const {
		return m_points.at(p_index);
	}

	auto begin() { return m_points.begin(); }
	auto end() { return m_points.end(); }
	auto begin() const { return m_points.begin(); }
	auto end() const { return m_points.end(); }
	auto cbegin() const { return m_points.cbegin(); }
	auto cend() const { return m_points.cend(); }


	void sort(bool reverse = true) {
		m_sorted = true;


		if (reverse) std::sort(m_points.begin(), m_points.end(), std::greater<>{});
		else std::sort(m_points.begin(), m_points.end(), std::less_equal<>());

	}


	const SimplexPoint<parameter_size>& getCentroid() {
		if (!m_centroid_valid) return m_centroid = calculateCentroid();
		return m_centroid;
	}

	bool isCentroidValid() const { return m_centroid_valid; }
	bool isSorted() const { return m_sorted; }


protected:
	std::array<SimplexPoint<parameter_size>, parameter_size + 1> m_points;
	SimplexPoint<parameter_size> m_centroid{};
	bool m_centroid_valid{ false };
	bool m_sorted{ false };

public:
	SimplexPoint<parameter_size> calculateCentroid() {
		m_centroid_valid = true;
		if (!m_sorted) sort();

		auto start = m_points.begin() + 1;
		auto end = m_points.end();

		SimplexPoint<parameter_size> base_point{};
		base_point.getData() = start->getData();
		base_point.onEvaluate(start->getCallback());

		SimplexPoint<parameter_size> centroid = std::accumulate(start, end, base_point);
		centroid /= parameter_size;

		return centroid;

	}

};

}