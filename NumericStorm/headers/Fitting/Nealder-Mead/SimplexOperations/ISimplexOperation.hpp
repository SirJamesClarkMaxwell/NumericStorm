#pragma once
#include "../SimplexFigure.hpp"
#include "SimplexOperationSettigns.hpp"
namespace NumericStorm
{
    namespace Fitting
    {

        template <size_t parameter_size>
        class ISimplexOperation
        {
        
        public:
            ISimplexOperation(const std::string &operationName, const SimplexOperationSettings &arguments)
                : m_operationName(operationName), m_settings(arguments){};

            virtual SimplexFigure<parameter_size> operator()( SimplexFigure<parameter_size> &simplexFigure) = 0;
            void updateSettigns(const SimplexOperationSettings &newSettings)
            {
                m_settings = newSettings;
            }

        protected:
            SimplexOperationSettings m_settings;
            std::string m_operationName;
        };

    }
}