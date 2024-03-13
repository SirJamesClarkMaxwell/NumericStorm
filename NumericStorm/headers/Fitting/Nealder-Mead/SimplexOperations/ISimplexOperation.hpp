#pragma once
#include "../SimplexFigure.hpp"
#include "SimplexOperationSettigns.hpp"
#include "../../CreatorInterface.hpp"

namespace NumericStorm
{
    namespace Fitting
    {

        

        template <size_t parameter_size>
        class ISimplexOperation : public CreatorInterface<SimplexFigure<parameter_size+1>&, SimplexFigure<parameter_size+1>&, SimplexOperationSettings>
        {
        public:

            using InterfaceType = CreatorInterface<SimplexFigure<parameter_size + 1>&, SimplexFigure<parameter_size + 1>&, SimplexOperationSettings>;
            using In = typename InterfaceType::In;
            using Out = typename InterfaceType::Out;
            using Settings = typename InterfaceType::Settings;
            ISimplexOperation() = default;
            ISimplexOperation(const ISimplexOperation<parameter_size>&) = default;
            ISimplexOperation(ISimplexOperation<parameter_size>&&) = default;
            ISimplexOperation<parameter_size>& operator=(const ISimplexOperation<parameter_size>&) = default;
            ISimplexOperation<parameter_size>& operator=(ISimplexOperation<parameter_size>&&) = default;

            virtual ~ISimplexOperation() = default;

           

            ISimplexOperation(const std::string& operationName, const SimplexOperationSettings& arguments)
                : CreatorInterface<In, Out, Settings>{} {
                m_operationName = operationName;
                this->m_settings = arguments;
            };

            const std::string& getOpeartionName() const { return m_operationName; }
        protected:
            std::string m_operationName{};
        };

    }
}