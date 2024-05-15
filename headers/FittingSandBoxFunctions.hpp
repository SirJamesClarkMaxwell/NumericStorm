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
			m_references[i] = m_ptr + i * size;
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
		: m_data((dimensions ? dimensions : 1)* (size ? size : 1), 0),
		m_dimensions(dimensions ? dimensions : 1),
		m_size(size ? size : 1) {}
	std::vector<double> get(int row)
	{
		std::vector<double> toReturn(m_size);
		for (int i = 0; i < m_size; i++)
			toReturn[i] = m_data[row * m_size + i];

		return toReturn;

	}
	void set(std::vector<double> newValues, int row)
	{
		for (int i = 0; i < m_size; i++)
			m_data[row * m_size + i] = newValues[i];
	};

	void presentData()
	{
		for (auto& it : m_data) { std::cout << it << " "; }
	}
private:
	//TODO change to size_t everywhere
	int m_dimensions;
	int m_size;

	std::vector<double> m_data{};
public:
	template<class T>
	class Iterator;

	struct Column {
		explicit Column(int col_size, int row_size, double* ptr) :
			m_col_size{ col_size },
			m_row_size{ row_size },
			m_val_ptr{ ptr } { }

		friend class Iterator<Column>;

		double& operator[](int index) {
			if (index < 0 || index >= m_col_size) return *m_val_ptr;
			return *(m_val_ptr + index * m_row_size);
		}
	private:
		int m_col_size{ 0 };
		int m_row_size{ 0 };
		double* m_val_ptr{ nullptr };

	private:
		Column operator++(int) {
			Column c = *this;
			m_val_ptr++;
			return c;
		}

		Column operator--(int) {
			Column c = *this;
			m_val_ptr--;
			return c;
		}

		bool operator==(const Column& other) {
			return m_val_ptr == other.m_val_ptr;
		}

		bool operator!=(const Column& other) {
			return m_val_ptr != other.m_val_ptr;
		}

	};
	struct Row {
		explicit Row(int col_size, int row_size, double* ptr) :
			m_col_size{ col_size },
			m_row_size{ row_size },
			m_val_ptr{ ptr } { }

		friend class Iterator<Row>;

		double& operator[](int index) {
			if (index < 0 || index >= m_row_size) return *m_val_ptr;
			return *(m_val_ptr + index * m_col_size);
		}

	private:
		int m_col_size{ 0 };
		int m_row_size{ 0 };
		double* m_val_ptr{ nullptr };

	private:
		Row operator++(int) {
			Row c = *this;
			m_val_ptr += m_row_size;
			return c;
		}

		Row operator--(int) {
			Row c = *this;
			m_val_ptr -= m_row_size;
			return c;
		}

		bool operator==(const Row& other) {
			return m_val_ptr == other.m_val_ptr;
		}

		bool operator!=(const Row& other) {
			return m_val_ptr != other.m_val_ptr;
		}

	};
	template<class T>
	class Iterator {
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = value_type*;
		using reference = value_type&;

		explicit Iterator(int col_size, int row_size, double* ptr) : m_slice{ col_size, row_size, ptr } { }
		Iterator<T> operator++(int) {
			Iterator<T> c = *this;
			m_slice++;
			return c;
		}

		Iterator<T>& operator++() {
			m_slice++;
			return *this;
		}

		Iterator<T> operator--(int) {
			Iterator<T> c = *this;
			m_slice--;
			return c;
		}
		Iterator<T>& operator--() {
			m_slice--;
			return *this;
		}

		T& operator*() {
			return m_slice;
		}

		bool operator==(const Iterator<T>& other) {
			return m_slice == other.m_slice;
		}

		bool operator!=(const Iterator<T>& other) {
			return m_slice != other.m_slice;
		}

	private:
		T m_slice{0, 0, nullptr };
	};

	struct RowOrder {
		friend class Data3;
		Iterator<Row> begin() { return Iterator<Row>(m_col_size, m_row_size, m_val_ptr); };
		Iterator<Row> end() { return Iterator<Row>(m_col_size, m_row_size, m_val_ptr + m_row_size); }

	private:
		explicit RowOrder(int col_size, int row_size, double* val_ptr)
			: m_col_size{ col_size },
			m_row_size{ row_size },
			m_val_ptr{ val_ptr } { }

		int m_col_size{ 0 };
		int m_row_size{ 0 };
		double* m_val_ptr{ nullptr };
	};

	struct ColumnOrder {
		friend class Data3;
		Iterator<Column> begin() { return Iterator<Column>(m_col_size, m_row_size, m_val_ptr); };
		Iterator<Column> end() { return Iterator<Column>(m_col_size, m_row_size, m_val_ptr + m_row_size); }

	private:
		explicit ColumnOrder(int col_size, int row_size, double* val_ptr)
			: m_col_size{ col_size },
			m_row_size{ row_size },
			m_val_ptr{ val_ptr } { }

		int m_col_size{ 0 };
		int m_row_size{ 0 };
		double* m_val_ptr{ nullptr };
	};

	RowOrder rowOrder() {
		return RowOrder(m_dimensions, m_size, &m_data[0]);
	}

	ColumnOrder columnOrder() {
		return ColumnOrder(m_dimensions, m_size, &m_data[0]);
	}

};
