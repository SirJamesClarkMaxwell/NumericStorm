# SimplexFigure

This class represents a simplex figure in n-dimensional space.
A simplex figure is a convex set of n+1 points, where n is the dimension of the space.
The points of the simplex are arranged in a specific order, known as the vertex arrangement,
which determines the shape of the figure. The centroid of the simplex is the center of gravity
of the points, and can be used to determine the location of the figure in space.

## Code

```cpp
using namespace NumericStorm::Fitting;
template<size_t parameter_size>

```
### Constructors
```cpp

SimplexFigure() {};
SimplexFigure( std::array<SimplexPoint<parameter_size>,parameter_size+1> points)
```
### Methods and member variables
```cpp
public:	
std::array<SimplexPoint<parameter_size >, parameter_size> getPoints() { return m_points; }
void sort(bool reverse = true);
SimplexPoint<parameter_size > getCentroid() { return m_centroid; }

protected:
std::array<SimplexPoint<parameter_size>, parameter_size+1> m_points;
SimplexPoint<parameter_size> m_centroid;

private:
	SimplexPoint<parameter_size> calculateCentroid();
```

## Explanation

The SimplexFigure class is templated on the number of parameters it represents. The template parameter is specified as a constant expression of type <span style = "color:green"> std::size_t </span>, which is an unsigned integer type that can represent the size of a container.

The SimplexFigure class has a default constructor, a copy constructor, and an assignment operator. It also provides a method for sorting the points of the simplex figure and a method for calculating the centroid of the simplex figure.

The class uses the SimplexPoint class to store the points of the simplex figure, and uses a private member variable to store the centroid of the simplex figure.

## Template Parameters

The SimplexFigure class has one template parameter: `parameter_size`. This parameter represents the dimension of the space, or the size of the parameter.

## Members

The SimplexFigure class has three members: `m_points`, `m_centroid`, and `parameter_size`.

- `m_points` is an array of SimplexPoint objects, which represents the points that make up the simplex figure.
- `m_centroid` is a SimplexPoint object that stores the centroid of the simplex figure.
- `parameter_size` is a constant expression of type std::size_t that represents the dimension of the space.

## Methods

The SimplexFigure class has three methods: `getPoints()`, `sort()`, and `getCentroid()`.

- `getPoints()` returns the points of the simplex figure.
- `sort()` sorts the points of the simplex figure in ascending order, and allows you to specify whether to sort in reverse order.
- `getCentroid()` returns the centroid of the simplex figure.

