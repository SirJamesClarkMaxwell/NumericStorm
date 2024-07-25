#pragma once

#include <vector>
#include <functional>

#include "OptimizerStateWrapper.hpp"
#include "StateWrapperBase.hpp"


namespace NumericStorm::Fitting
{
	using namespace NumericStorm::Concepts;
	
	template<OptimizerStateWrapper WrappedState>
    class AnnealingOptimizerState : public StateWrapperBase<WrappedState> {
    public:

        AnnealingOptimizerState(const WrappedState& state)
			: StateWrapperBase<WrappedState>{ state } {}

        std::vector<double*>& getEnergies() {
            return m_energies;
        }

        const std::vector<double*>& getEnergies() const {
            return m_energies;
        }

        std::vector<std::vector<double*>>& getConfigurations() {
            return m_configurations;
        }

        const std::vector<std::vector<double*>>& getConfigurations() const {
            return m_configurations;
        }

        double getEnergy(const std::vector<double>& config) const {
            if (m_energyCallback) return m_energyCallback(config);
            return -1.0;
        }

        void setCallback(const std::function<double(const std::vector<double>&)>& callback) {
            m_energyCallback = callback;
        }


        double& getTemperature() const {
			return m_temperature;
		}

        auto& getAnnealedConfigurations() {
            return m_annealedConfigurations;
        }

        auto& getAnnealedEnergies() {
			return m_AnnealedEnergies;
		}

        auto& getBackOffset() {
            return m_back_offset;
        }


    private:
        std::vector<double*> m_energies{};
        std::vector<std::vector<double*>> m_configurations{};
        std::function<double(const std::vector<double>&)> m_energyCallback{};

        std::vector<std::vector<double>> m_annealedConfigurations{};
        std::vector<double> m_AnnealedEnergies{};
        size_t m_back_offset{};
        double m_temperature{};
    };
};