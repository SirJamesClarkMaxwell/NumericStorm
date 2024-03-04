# ErrorModel class

The ErrorModel class is an abstract base class that defines the interface for all error models used in the fitting process.

An error model is a function that maps a pair of data points to a scalar error value. The error model is used to quantify the uncertainty associated with a fitted curve or surface.

The ErrorModel class provides a virtual operator() method that must be implemented by derived classes. The operator() method takes two data points (referencedData and comparedData) as input and returns a double value that represents the error between the two data points.

## Member functions

```cpp
ErrorModel(std::function<double(const Data& referenceData, const Data& evaluatedData)> errorModel)
```

The constructor that takes an error function.

```cpp
virtual double operator()(const Data& referencedData, const Data& comparedData) = 0;
```

Evaluates the error model.
