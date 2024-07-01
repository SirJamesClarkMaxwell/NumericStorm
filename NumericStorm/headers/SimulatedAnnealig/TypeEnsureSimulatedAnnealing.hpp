#pragma once 
#include <math.h>
#include <array>
#include <vector>
#include <memory>
#include "Random.hpp"
// #include "./../BasicSimplex/BasicSimplexOptimizer.hpp"
// #include "./../../SimulatedAnnealig/SimulatedAnnealingFactory.hpp"
namespace NumericStorm::SimulatedAnnealing
{
//template<class SerializeOutput>
class InputConcept
{
public:
    virtual ~InputConcept() = default;
    virtual double getEnergy() = 0;
    virtual std::vector<double> serialize() = 0;
    // virtual std::vector<SerializeOutput> serialize() = 0; //! do we need this?
    virtual std::unique_ptr<InputConcept> createObject(const std::vector<double>& inputData)const = 0;
};
template< class AnnealingWrapper>
class OwningAnnealingModel :public InputConcept
{
public:
    OwningAnnealingModel(AnnealingWrapper strategy)
        :, m_wrapper{ wrapper } {};
    template<class AnnealingObject>
    std::vector<double> serialize(const AnnealingObject& object) { return m_wrapper.doSerialize(object); };
    template<class AnnealingObject>
    double getEnergy(const AnnealingObject& object) { return m_wrapper.getEnergy(object); };
    std::unique_ptr<AnnealingObject> createObject(std::vector<double> inputData)
    {
        m_wrapper.do_object(inputData)
    };
private:
    AnnealingWrapper m_wrapper;
};
// template<class AnnealingType>
class SimulatedAnnealingFactoryTypeEnsure
{
public:
    template<class AnnealingWrapper>
    SimulatedAnnealingFactoryTypeEnsure(AnnealingWrapper wrapper)
    {
        using Model = OwningAnnealingModel<AnnealingWrapper>;
        m_pointerToImplementation = std::make_unique<Model>(std::move(wrapper));
    }
private:
    std::unique_ptr<InputConcept> m_pointerToImplementation;
    template<class AnnealingType>
    friend double getEnergy(const SimulatedAnnealingFactoryTypeEnsure& factory, const AnnealingType& object)
    {
        return factory.m_pointerToImplementation->getEnergy(object);
    };
    template<class AnnealingType>
    friend std::vector<double> serialize(const SimulatedAnnealingFactoryTypeEnsure& factory, const AnnealingType& object) { return factory.m_pointerToImplementation->serialize(object); };
    friend std::unique_ptr<InputConcept> createObject(const SimulatedAnnealingFactoryTypeEnsure& factory, std::vector<double> inputData) { return factory.m_pointerToImplementation->createObject(inputData); };
};
};

