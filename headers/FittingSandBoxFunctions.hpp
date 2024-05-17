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
		//std::cout << duration << "us (" << ms << "ms)" << std::endl;
		return ms;
	};
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;


};
double testingDataClass();
double testingIteratedDataClass();

using namespace NumericStorm::Fitting;

class GaussianModel : public Model<4> {
public:
	GaussianModel() : Model<4>{ gaussianFunction } {};

	static void gaussianFunction(Data& datum, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
	{
		double A = parameters[0];
		double mu = parameters[1];
		double sigma = parameters[2];
		double c = parameters[3];

		for (int i = 0; i < datum[0].size(); i++)
		{
			double updatedX = (datum[0][i] - mu);
			datum[1][i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
		}
	}
};



class IteratedData
{
public:
	using TypeName = double;
public:
	IteratedData(int dimensions, int size)
		: m_data((dimensions ? dimensions : 1)* (size ? size : 1), 0),
		m_dimensions(dimensions ? dimensions : 1),
		m_size(size ? size : 1) {}
	std::vector<double> get(int column)
	{
		std::vector<double> toReturn(m_size);
		for (int i = 0; i < m_size; i++)
			toReturn[i] = m_data[i * m_dimensions + column];

		return toReturn;

	}
	void set(std::vector<double> newValues, int column)
	{
		for (int i = 0; i < m_size; i++)
			m_data[i * m_dimensions + column] = newValues[i];
	};

	void presentData()
	{
		for (auto row : rowOrder()) {
			for (int i = 0; i < m_size; i++) {
				std::cout << row[i] << std::endl;
			}
			std::cout << std::endl;
		}
	}
private:
	//TODO change to size_t everywhere
	int m_dimensions;
	int m_size;

	std::vector<double> m_data{};
public:
	class RowIterator;

	struct Row {
		explicit Row(int column_size, int row_size, double* ptr) :
			m_column_size{ column_size },
			m_row_size{ row_size },
			m_val_ptr{ ptr } { }

		friend class RowIterator;

		double& operator[](int index) {
			if (index < 0 || index >= m_row_size) return *m_val_ptr;
			return *(m_val_ptr + index * m_column_size);
		}

	private:
		int m_column_size{ 0 };
		int m_row_size{ 0 };
		double* m_val_ptr{ nullptr };

	private:
		void operator++(int) {
			m_val_ptr++;
		}

		void operator--(int) {
			m_val_ptr--;
		}

		bool operator==(const Row& other) {
			return m_val_ptr == other.m_val_ptr;
		}

		bool operator!=(const Row& other) {
			return m_val_ptr != other.m_val_ptr;
		}

	};

	class ColumnIterator {
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = double;
		using pointer = value_type*;
		using reference = value_type&;

		explicit ColumnIterator(int column_size, int row_size, double* ptr) :
			m_column_size{ column_size },
			m_row_size{ row_size },
			m_val_ptr{ ptr } { }


		ColumnIterator operator++(int) {
			ColumnIterator copy = *this;
			m_val_ptr += m_column_size;
			return copy;
		}

		ColumnIterator& operator++() {
			m_val_ptr += m_column_size;
			return *this;
		}

		ColumnIterator operator--(int) {
			ColumnIterator copy = *this;
			m_val_ptr -= m_column_size;
			return copy;
		}
		ColumnIterator& operator--() {
			m_val_ptr -= m_column_size;
			return *this;
		}

		double* operator*() {
			return m_val_ptr;
		}

		double& operator[](int index) {
			if (index < 0 || index >= m_column_size) return *m_val_ptr;
			return *(m_val_ptr + index);
		}

		bool operator==(const ColumnIterator& other) {
			return m_val_ptr == other.m_val_ptr;
		}

		bool operator!=(const ColumnIterator& other) {
			return m_val_ptr != other.m_val_ptr;
		}

	private:
		int m_column_size{ 0 };
		int m_row_size{ 0 };
		double* m_val_ptr{ nullptr };
	};

	class RowIterator {
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = double;
		using pointer = value_type*;
		using reference = value_type&;

		explicit RowIterator(int column_size, int row_size, double* ptr) :
			m_row{ column_size, row_size, ptr },
			m_column_size{ column_size },
			m_row_size{ row_size } { }


		RowIterator operator++(int) {
			RowIterator copy = *this;
			m_row++;
			return copy;
		}

		RowIterator& operator++() {
			m_row++;
			return *this;
		}

		RowIterator operator--(int) {
			RowIterator copy = *this;
			m_row--;
			return copy;
		}
		RowIterator& operator--() {
			m_row--;
			return *this;
		}

		Row& operator*() {
			return m_row;
		}

		bool operator==(const RowIterator& other) {
			return m_row == other.m_row;
		}

		bool operator!=(const RowIterator& other) {
			return m_row != other.m_row;
		}

	private:
		int m_column_size{ 0 };
		int m_row_size{ 0 };
		Row m_row{ 0, 0, nullptr };
	};

	struct RowOrder {
		friend class IteratedData;
		RowIterator begin() { return RowIterator(m_column_size, m_row_size, m_val_ptr); };
		RowIterator end() { return RowIterator(m_column_size, m_row_size, m_val_ptr + m_column_size); }

	private:
		explicit RowOrder(int column_size, int row_size, double* val_ptr) :
			m_column_size{ column_size },
			m_row_size{ row_size },
			m_val_ptr{ val_ptr } { }

		int m_column_size{ 0 };
		int m_row_size{ 0 };
		double* m_val_ptr{ nullptr };
	};

	struct ColumnOrder {
		friend class IteratedData;
		ColumnIterator begin() { return ColumnIterator(m_column_size, m_row_size, m_val_ptr); };
		ColumnIterator end() { return ColumnIterator(m_column_size, m_row_size, m_val_ptr + m_column_size * m_row_size); }

	private:
		explicit ColumnOrder(int column_size, int row_size, double* val_ptr) :
			m_column_size{ column_size },
			m_row_size{ row_size },
			m_val_ptr{ val_ptr } { }

		int m_column_size{ 0 };
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


