#pragma once

#include <functional>
#include "AdditionalParameters.hpp"
#include "Data.hpp"
#include "Parameters.hpp"



namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
class ModelBase
{
public:
    static const size_t parameter_size = parameter_size;
    using AuxParameters = AuxilaryParameters;
    using ModelFunction = std::function<void(Data&, const Parameters<parameter_size>&, const AuxParameters&)>;
    
    ModelBase() = default;

    ModelBase(const ModelFunction& model)
        : m_model{ model } {};

   
    virtual ~ModelBase() = default;

    void operator()(Data& arguments, const Parameters<parameter_size>& parameters, const AuxParameters& additionalParameters) const {
        m_model(arguments, parameters, additionalParameters);
    }

    auto getModel() const {
		return m_model;
	}

    void setModel(const ModelFunction& model) {
		m_model = model;
	}

	bool isModelValid() const {
		return m_model != nullptr;
	}

protected:
    ModelFunction m_model;
};

}
}
