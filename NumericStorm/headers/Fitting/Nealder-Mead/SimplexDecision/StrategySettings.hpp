#pragma once

namespace NumericStorm {
namespace Fitting {
template<size_t parameter_size>
class StrategySettings {
	//NU I need the explanation of this class, why we need it?
	int getBestInd() const { return m_best_point_ind; }
	int getWorstInd() const { return m_worst_point_ind; }
	int getSecondWorstInd() const { return m_second_worst_ind; }

private:
	const int m_best_point_ind{ parameter_size };
	const int m_worst_point_ind{ 0 };
	const int m_second_worst_ind{ 1 };
};
}
}