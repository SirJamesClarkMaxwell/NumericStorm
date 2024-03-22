# SimplexPoint

This class represents a point in the simplex, which is a mathematical concept used in optimization.
A simplex point is defined by a set of parameters and an additional set of parameters that can be used to store
additional information about the point, such as an error value or a model prediction.

The SimplexPoint class provides a set of operators for manipulating points, as well as methods for setting and
calculating the error and model prediction for a point.

## Code

```cpp
using namespace NumericStorm ::Fitting ;
template <std::size_t parameter_size>
```

### Constructors

```cpp
SimplexPoint() = default;
SimplexPoint(std::array<double, parameter_size> parameters, AdditionalParametersadditionalParameters);
SimplexPoint(const SimplexPoint<parameter_size>& other) = default;
```

### Methods and Operators

#### Operator for numeric types

- `*=`, `/=`

#### Operator for SimplexPoint

- `==`, `== const`,`!=`,`<=`,`>=`,`<`,`>`,`=`,`+=`,`-=`,`+`,`-`

```cpp
double& operator[](int index);
const double& operator[](int index) const;=
std::array<double, parameter_size> getParameters() const;

void setUp(std::shared_ptr<Model<parameter_size>> dataModel, std::shared_ptr<ErrorModel> errorModel);
void calculateError(const Data& referenceData, const Data& calculatedData);
Data calculateData() const;
```

#### member variables

```cpp
private:

Parameters<parameter_size> m_parameters;
AdditionalParameters m_additionalParameters;
double m_error;
bool m_modelSet;
bool m_errorModelSet;
std::shared_ptr<Model<parameter_size>> m_model;
std::shared_ptr<ErrorModel> m_errorModel;
```

## Explanation

The SimplexPoint class is templated on the number of parameters it represents. The template parameter is specified as a constant expression of type <span style= "color:green"> std::size_t
</span>, which is an unsigned integer type that can represent the size of a container.

The SimplexPoint class has a default constructor, a copy constructor, and an assignment operator. It also provides overloaded operators for comparing two SimplexPoints, accessing the parameters, and performing arithmetic operations on SimplexPoints.

The class provides methods for setting the model and error model for a simplex point, calculating the error for a simplex point, and calculating the data for a simplex point.

The SimplexPoint class uses the Parameters and AdditionalParameters classes to store the parameters and additional parameters, respectively. The Parameters class is a simple container class that stores the parameters as an array of doubles, while the AdditionalParameters class is a struct that stores additional information about the point needs to evaluate the Data in this point in space.

The SimplexPoint class uses a private member variable to store the error value, a boolean flag to indicate whether the model has been set, and a pointer to the model and error model.

## Operators

The SimplexPoint class provides overloaded operators for comparison, subscripting, and arithmetic operations.

The comparison operators == and != compare two SimplexPoints for equality or inequality, respectively. The comparison operators <=, >=, <, and > compare two SimplexPoints and return true if the first SimplexPoint has a lower/higher/different error value and/or a different set of parameters, respectively.

The subscript operator [] allows you to access the parameters of the SimplexPoint by index. If the index is out of range, the operator returns the first/last parameter.

The arithmetic operators +, -, \*, and / allow you to perform addition, subtraction, multiplication, and division operations on SimplexPoints and scalar values.

## Methods

The SimplexPoint class provides several methods for setting up, calculating the error, and calculating the data for a simplex point.

The `setUp` method takes two arguments: a pointer to a `Model` object for calculating the data and a pointer to an `ErrorModel` object for calculating the error. The method sets the model and error model for the simplex point.

The `calculateError` method takes two arguments: a reference to a Data object for the reference data. The method calculates the error for the simplex point using the reference data and calculated data.

The `calculateData` method calculates the data for the simplex point using the currently set model.

## Exceptions

The SimplexPoint class throws two exceptions: `NoSetErrorModelExeption` and `NoSetModelExeption`. These exceptions are thrown when the error model or model has not been set, respectively.

# Example of usage

```cpp
std::vector<double> arguments{ -2, -1, 0, 1, 2 };
std::array<double, 4> referencedArray{ 2, 1, 2, -1 };
AdditionalParameters additionalParameters{};
std::shared_ptr<Model<4>> gaussianModel = std::make_shared<GaussianModel>();
std::shared_ptr<ErrorModel> chi2ErrorModel= std::make_shared<Chi2ErrorModel>();

SimplexPoint<4> referencedSimplexPoint(arguments, referencedArray, additionalParameters);
referencedSimplexPoint.setUp(gaussianModel, chi2ErrorModel);
std::shared_ptr<Data> referencedData_unique_ptr = referencedSimplexPoint.calculateData();
auto referencedValues = (*referencedData).getValues();
evaluatedSimplexPoint.calculateError(referencedData);
double error = evaluatedSimplexPoint.getError();
```
