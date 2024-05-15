#pragma once 
#include <cmath>
#include <iomanip>
#include <tuple>
#include <chrono>
#include "NumericStorm.hpp"

class Timer
{
public:

    Timer()
    {
        m_StartTimePoint = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {}
    double stop()
    {
        auto endTimePoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
        auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

        auto duration = stop - start;
        double ms = duration * 0.001;
        std::cout << duration << "us (" << ms << "ms)" << std::endl;
        return ms;
    };
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;


};


using namespace NumericStorm::Fitting;
void testingParameters();

class GaussianModel : public Model<4>
{
public:
    GaussianModel()
        : Model<4>{ gaussianFunction } {}
    static void gaussianFunction(Data& datum, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters);

};
class Chi2ErrorModel : public ErrorModel {
public:

    Chi2ErrorModel() : ErrorModel{ chi2ErrorModelFunction } {}

    static double chi2ErrorModelFunction(const Data& referenceData, const Data& evaluatedData);
};

void testingModelAndErrorModel();


class Data2
{
public:
    Data2(int dimensions, int size)
        :m_dimensions(dimensions), m_size(size)
    {
        m_data.resize(dimensions * size);
    }
    std::vector<double> get(int index)
    {
        std::vector<double> toReturn(m_size);
        for (int i = 0; i < m_size; i++)
            toReturn[i] = m_data[index * m_size + i];

        return toReturn;

    }
    void set(std::vector<double> newValues, int index)
    {
        for (int i = 0; i < m_size; i++)
            m_data[index * m_size + i] = newValues[i];
    }
    void presentData()
    {
        for (int i = 0; i < m_dimensions; i++)
        {
            for (int j = 0; j < m_size; j++)
            {
                m_data[i * m_size + j] = j;
                std::cout << m_data[i * m_size + j] << " ";
            }
            std::cout << std::endl;
        }
    }
private:
    int m_dimensions;
    int m_size;
    std::vector<double> m_data{};


};


class Data3;


class Data3Iterator
{
public:
    using PointerType = double*;
    using ReferencedType = double&;
    Data3Iterator(int dimensions, int size, const PointerType& ptr)
        :m_size{ size }, m_dimensions{ dimensions }, m_ptr{ ptr }
    {
        m_references.resize(m_dimensions);
        for (int i = 0; i < dimensions; i++)
            m_references[i] = m_ptr + i *size;
    };
    Data3Iterator operator++()
    {
        for (auto& reference : m_references)
            reference++;
        m_ptr++;
        return *this;
    }
    Data3Iterator operator++(int)
    {
        Data3Iterator temp = *this;
        ++(*this);

        return temp;
    }
    Data3Iterator operator--()
    {
        for (auto& reference : m_references)
            reference--;
        return *this;
    }
    Data3Iterator operator--(int)
    {
        Data3Iterator temp = *this;

        --(*this);

        return temp;
    }
    PointerType& operator[](int index) { return m_references[index]; }
    std::vector<PointerType> operator*()
    {
        std::vector<PointerType> toReturn(m_size);
        for (int i = 0; i < m_dimensions; ++i)
            toReturn[i] = m_references[i];
        return toReturn;
    }
    bool operator==(const Data3Iterator& other)
    {
#if 0
        for (int i = 0; i < m_dimensions; i++)
            if (m_references[i] != other[i])
                return false;
        return true;
#endif
        //bool value = m_references == other.m_references;
		//bool value = m_references[m_dimensions - 1] == other.m_references[m_dimensions - 1];
        bool value = m_ptr == other.m_ptr;
        return value;
    }
    bool operator!=(const Data3Iterator& other)
    {
        return !(*this == other);
    }
private:
    int m_size;
    int m_dimensions;
    std::vector<PointerType> m_references;
public:
    PointerType m_ptr;
};


class Data3
{
public:
    using TypeName = double;
public:
    Data3(int dimensions, int size)
        :m_dimensions(dimensions), m_size(size)
    {
        m_data.resize(dimensions * size);
    }
    std::vector<double> get(int index)
    {
        std::vector<double> toReturn(m_size);
        for (int i = 0; i < m_size; i++)
            toReturn[i] = m_data[index * m_size + i];

        return toReturn;

    }
    void set(std::vector<double> newValues, int index)
    {
        for (int i = 0; i < m_size; i++)
            m_data[index * m_size + i] = newValues[i];
    };


    void presentData()
    {
        for (auto& it : m_data) { std::cout << it << " "; }
    }
private:
    int m_dimensions;
public:
    int m_size;
    std::vector<double> m_data{};
public:
    Data3Iterator begin() { return Data3Iterator(m_dimensions, m_size, &m_data[0]); };
    Data3Iterator end() { return Data3Iterator(m_dimensions, m_size, &m_data.at(m_size)); }

};