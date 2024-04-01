#pragma once
#include <memory>
#include <functional>

#include "Model.hpp"
#include "ErrorModel.hpp"
#include "Bounds.hpp"
#include "AdditionalParameters.hpp"
namespace NumericStorm
{
namespace Fitting
{
template <size_t parameter_size, class AuxilaryParameters = AdditionalParameters<parameter_size>>
class FitterSettings
{
public:
	FitterSettings(const std::shared_ptr<Model<parameter_size, AuxilaryParameters>>& model, const std::shared_ptr<ErrorModel>& errorModel, const AuxilaryParameters& add_params, long int maxIteration, double minError, bool useBounds)
		: m_functionModel{ model }, m_errorModel{ errorModel }, m_maxIteration{ maxIteration }, m_minError{ minError }, m_add_params{ add_params }, m_useBounds(useBounds) {}
	FitterSettings() = delete;
	FitterSettings(const FitterSettings<parameter_size, AdditionalParameters>&) = default;
	FitterSettings(FitterSettings<parameter_size, AdditionalParameters>&&) = default;
	FitterSettings<parameter_size, AuxilaryParameters>& operator=(const FitterSettings<parameter_size, AuxilaryParameters>&) = default;
	FitterSettings<parameter_size, AuxilaryParameters>& operator=(FitterSettings<parameter_size, AuxilaryParameters>&&) = default;

	virtual ~FitterSettings() = default;

	//there is no reason for this to be an abstract class since all the methods return data defined in this very class
	virtual const Model<parameter_size, AuxilaryParameters>& getFunctionModel() const { return *m_functionModel; };
	virtual const ErrorModel& getErrorModel() const { return *m_errorModel; }
	virtual double getMinError() const { return m_minError; }
	virtual long int getMaxIteration() const { return m_maxIteration; }
	//todo implement builderPattern 
protected:
	AuxilaryParameters m_add_params{};
	//BUG Model and ErrorModel must be a some type of pointer, probably the shared_one. In other case the user will not have possibility to pass a derived classes 
	std::shared_ptr<Model<parameter_size, AuxilaryParameters>> m_functionModel;
	std::shared_ptr<ModelErrorModel> m_errorModel;

	//NOTE we should carful with this unique pointer. If user will move them, it will lose the data
	//Proposition make this pointer const, but this will not allow us to set this later even in constructor if we initialize it by nullptr only getting the data will be possible	
	//Proposition const mutable std::unique_ptr<Data> m_ref_data{ nullptr };
	std::shared_ptr<Data> m_ref_data{ nullptr }; //NOTE what i prefer. 
	long int m_maxIteration{ 1000 };
	double m_minError{ 0.1 };
	bool m_useBounds{ false };

};
}

}