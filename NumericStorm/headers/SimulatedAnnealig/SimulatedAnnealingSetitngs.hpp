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
    };

};