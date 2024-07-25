#pragma once


namespace NumericStorm::Annealing
{
    class SimulatedAnnealingSettings {
    public:
      
        double getCoolingRate() const {
            return m_coolingRate;
        }
    
        double getNoiseFactor() const {
            return m_noiseFactor;
        }
    
        double getInitialTemp() const {
            return m_initialTemperature;
        }
    
        double getK() const {
            return m_k;
        }
    
        size_t getNumberToAnneal() const {
            return m_numberOfPointsToAnneal;
        }
    
    private:
        double m_coolingRate{0.0 };
        double m_noiseFactor{ 0.0 };
        double m_initialTemperature{ 0.0 };
        double m_k{ 1.0 };
        size_t m_numberOfPointsToAnneal{ 1 };
		friend class AnnealingSettingsBuilder;

    public:
		
		
    };

	class AnnealingSettingsBuilder {
	private:
		using Settings = SimulatedAnnealingSettings;
	public:

		Settings build() { return m_settingsObject; }


		AnnealingSettingsBuilder& coolingRate(double rate)
		{
			this->m_settingsObject.m_coolingRate = rate;
			return returnSelf();
		}

		AnnealingSettingsBuilder& noiseFactor(double factor)
		{
			this->m_settingsObject.m_noiseFactor = factor;
			return returnSelf();
		}

		AnnealingSettingsBuilder& initialTemperature(double temperature)
		{
			this->m_settingsObject.m_initialTemperature = temperature;
			return returnSelf();
		}
		AnnealingSettingsBuilder& constantK(double k)
		{
			this->m_settingsObject.m_k = k;
			return returnSelf();
		}
		AnnealingSettingsBuilder& pointNumber(size_t number)
		{
			this->m_settingsObject.m_numberOfPointsToAnneal = number;
			return returnSelf();
		}

	protected:
		AnnealingSettingsBuilder& returnSelf() { return *this; }

	protected:
		Settings m_settingsObject{};

	};
};