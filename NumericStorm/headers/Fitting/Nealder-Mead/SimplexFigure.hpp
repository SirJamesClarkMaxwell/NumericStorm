#pragma once
#include "SimplexPoint.hpp"
#include <numeric>

namespace NumericStorm {
namespace Fitting {


template<size_t parameter_size>
class SimplexFigure {
public:
	SimplexFigure() = default;
	SimplexFigure(const SimplexFigure<parameter_size>&) = default;
	SimplexFigure(SimplexFigure<parameter_size>&&) = default;
	SimplexFigure<parameter_size>& operator=(const SimplexFigure<parameter_size>&) = default;
	SimplexFigure<parameter_size>& operator=(SimplexFigure<parameter_size>&&) = default;

	virtual ~SimplexFigure() = default;

	//changed back because the order is actually defined in the way the fields are declared
	SimplexFigure(const std::array<SimplexPoint<parameter_size>, parameter_size + 1>& points) 
		: m_points{ points }, m_centroid{ calculateCentroid() } {}

	const std::array<SimplexPoint<parameter_size>, parameter_size + 1>& getPoints() const { return m_points; }


	SimplexPoint<parameter_size>& operator[](int p_index) {
		m_centroid_valid = false;
		m_sorted = false;

		if (p_index > parameter_size || p_index < 0) {
			throw std::out_of_range("Index out of bounds");
		}
		return m_points[p_index];
	}

	const SimplexPoint<parameter_size>& operator[](int p_index) const {

		if (p_index > parameter_size || p_index < 0) {
			throw std::out_of_range("Index out of bounds");
		}
		return m_points[p_index];
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
	//TODO remove this method and fields and move this responsibility into IDecision
	SimplexPoint<parameter_size>& getReflected() { return m_reflected; }
	const SimplexPoint<parameter_size>& getReflected() { return m_reflected; }

	SimplexPoint<parameter_size>& getFinal() { return m_final; }
	const SimplexPoint<parameter_size>& getFinal() { return m_final; }

protected:
	std::array<SimplexPoint<parameter_size>, parameter_size + 1> m_points{};
	SimplexPoint<parameter_size> m_centroid{};
	SimplexPoint<parameter_size> m_reflected{};
	//Q what is the final? 
	/*
	is it returned parameters? why we need them if fit/minimize function will return it?
	*/
	SimplexPoint<parameter_size> m_final{};
	bool m_centroid_valid{ false };
	bool m_sorted{ false };

private:
	SimplexPoint<parameter_size> calculateCentroid() {
		m_centroid_valid = true;
		if (!m_sorted) sort(); //we must sort because we dont want to include the worst point specifically
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