#include <unordered_map>
#include <string>
#include <vector>
#include "../SimplexFigure.hpp"

namespace NumericStorm
{
	namespace Fitting
	{

		template <size_t parameter_size>
		class IDecision
		{
		public:
			IDecision() = default;
			virtual ~IDecision() = default;
			virtual SimplexFigure<parameter_size> makeDecision(const std::vector<SimplexFigure<parameter_size>> &simplexFigures) = 0;
		};

	}
}