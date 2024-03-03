#include <unordered_map>
#include <string>

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
            virtual SimplexFigure<parameter_size> makeDecision(std::array<SimplexFigure<parameter_size>, parameter_size + 1> simplexFigures) = 0;
        };

    }
}