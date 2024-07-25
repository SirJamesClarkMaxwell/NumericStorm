#pragma once
#include <array>
#include <iostream>
#include <stdexcept>
#include <utility>



namespace NumericStorm::Fitting {



template <size_t parameter_size>
    class Parameters {
    public:
        Parameters(const std::array<double, parameter_size>& parameters)
            : m_parameters{ parameters } {}
        
       
        virtual ~Parameters() = default;
    
        const std::array<double, parameter_size>& getParameters() const { return m_parameters; };
        std::array<double, parameter_size>& getParameters() { return m_parameters; };
    
        virtual double& operator[](size_t index)
        {
            return m_parameters.at(index);
        }
        virtual const double& operator[](size_t index) const
        {
            return m_parameters.at(index);
        }

        auto begin() { return m_parameters.begin(); }
        auto end() { return m_parameters.end(); }
        auto begin() const { return m_parameters.begin(); }
        auto end() const { return m_parameters.end(); }
        auto cbegin() const { return m_parameters.cbegin(); }
        auto cend() const { return m_parameters.cend(); }
    
    private:
        std::array<double, parameter_size> m_parameters{};
        
    };
}



