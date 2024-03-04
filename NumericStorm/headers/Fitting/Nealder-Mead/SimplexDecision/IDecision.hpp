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
			//! probably makeDecision should have an optional argument and there we could store the points from annealing
			//! or we could create another method with one additional argument, and later in some way set things up by another method
			//! but this will be quite slow because in that case we will need to set things up in every iteration of the algorithm
		};

	}
}