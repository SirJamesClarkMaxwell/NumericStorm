## General Description of the Abstract Model Class

This abstract class is responsible for holding information about the function that will calculate the data needed to evaluate the goal function in the fitting procedure. This is achieved using <span style = "color:green">std::function<> </span>.

### Constructor:

```cpp
Model(std::function<std::unique_ptr<Data>(
    const std::vector<double>& arguments,
    const Parameters<parameter_size>& parameters,
    const AdditionalParameters& additionalParameters)> model)
```

Let's go break this down piece by piece:

- the return value is the unique pointer in <span style = "color: lightblue">abstract</span> <span style = "color: green"> Data</span> class
- The fist argument is `arguments` which is as <span style ="color: green"> std::vector </span> <<span style = "color: lightblue">double</span></span>> , These are the x-values for standard mathematical functions.
- <span style = "color: green"> Parameters </span> This object will be fitted inside the fitter class.
- <span style="color: green"> AdditionalParameters</span> this argument is optional. If the function requires any other additional parameters to return the correct result, this is the right place to store this type of information.
  All arguments are passed by const reference to avoid unnecessary copies of this potentially heavy object.

The return type is a unique pointer because we don't want to return data by value, as it may be heavy. Moreover, we don't want multiple pointers to the same block of memory, so unique pointers are used.

One more addition to this description of the class: because this is an abstract class, you need to implement the function call operator. Additionally, you need to implement the concrete <span style="color:green"> Data </span> class by inheriting from it.

This class is the abstract responsible for holding the information about the function that will be responsible for calculating the data needed to evaluating the goal function in fitting procedure. This is done by <span style=" color: green"> std::function<>. </span>

### Constructor:

```cpp
Model(std::function<std::unique_ptr<Data>(
    const std::vector<double>& arguments,
    const Parameters<parameter_size>& parameters,
    const AdditionalParameters& additionalParameters)> model)
```

### Overloaded calling operator:

<!-- TODO: add this section about the logic how this operator is working and add the short description of how we are returning the shared pointer instead of unique one -->

<!-- TODO add note that it will change in time, and to be sure what you need to pass into the operator check the source code -->

Let's go break this out piece by piece:

- the returning value is the unique pointer into <span style = "color: lightblue">abstract</span> <span style = "color: green"> Data</span> class
- <span style ="color: green"> std::vector </span> <<span style = "color: lightblue">double</span></span>> the fist argument is arguments, this is just a set of x's for standard mathematical functions
- <span style = "color: green"> Parameters </span> This is the the object that will be fitted inside the fitter class.
- <span style="color: green"> AdditionalParameters</span> this argument will optional. If function needs any other additional parameters to return correct result this is the right place to store this type of information

All arguments are passed by const reference, because we want to avoid unnecessary copies of this potentially heavy object.

The return type is a unique pointer because we don't want to return data by value. This will potentially be a heavy item. Moreover, we don't particularly want to have multiple pointers to the same block of memory -> unique pointers arrived.

One more addition to this description of class, because this is the abstract class you need to implement the calling operator. And also you need to implement the concrete <span style="color:green"> Data </span> class by inheriting from it.

# Example of usage

All code of declared function will be available in the end of this file, in table of context it will marked as the `Full Code`
This class could be used in in two different ways:

1.  By a roll classes
2.  By derived classes

We highly suggest to use the second option, your code will be cleaner and more easier to change in the future. But we want to mark it that there is a another way how you can use this class. In both cases we will implement a standard Gaussian function.

### Using this class by roll class:

#### 1. We need to define a function that will calculate the Data, itself.

```cpp
std::unique_ptr<Data> gaussian(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
  {...};
```

#### 2. Declare arguments, parameters and additional parameters

```cpp
std::array<double, 4> referencedArray{ 2, 1, 2, -1 };
Parameters<4> referencedParameters{ referencedArray };
std::vector<double> arguments{ -2, -1, 0, 1, 2 };
AdditionalParameters additionalParameters;

std::function<std::unique_ptr<Data>(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)> gaussianFunction = gaussian;
```

#### 3. Invoke the calling operator

```cpp
Model<4> model = Model(gaussianFunction);
std::shared_ptr<Data> calculatedData = model(arguments,referencedParameters,additionalParameters);
```

### Using this class as derived class:

#### 1. Creating a derived class from Model

You could encounter that the function is marked as a static one, it is not a std::function type. But we this code is working, because the implicit conversion, which is generally not a good thing but here we accept it, because we have a control on this, and what is more important we know about this implicit conversion.

```cpp
class GaussianModel : public Model<4> {
public:
    GaussianModel()
      :Model<4>(gaussianFunction) {};

    static std::unique_ptr<Data> gaussianFunction(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters);

    std::shared_ptr<Data> operator()(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters);
};
```

#### 2. Creating the shared pointer into the object of class GaussianModel

```cpp
std::array<double, 4> referencedArray{ 2, 1, 2, -1 };
Parameters<4> referencedParameters{ referencedArray };
std::vector<double> arguments{ -2, -1, 0, 1, 2 };

AdditionalParameters additionalParameters;
std::shared_ptr<Model<4>> gaussianModel = std::make_shared<GaussianModel>();
Parameters<4> parameters{ std::array<double, 4>{1, 1, 1, 1} };
SimplexPoint<4> referencedPoint(arguments, parameters, additionalParameters);
referencedPoint.setUp(gaussianModel, chi2ErrorModel);
std::shared_ptr<Data> referencedData = referencedPoint.calculateData();
```

# Full Code

#### Gaussian function

```cpp
std::unique_ptr<Data> gaussian(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters) {
    std::vector<double> calculatedData;
    calculateData.resize(arguments.size());
    double A = parameters[0], mu = parameters[1], sigma = parameters[2], c = parameters[3];

    for (int i = 0; i < arguments.size(); i++)
    {
        double updatedX = (arguments[i] - mu);
        calculateData[i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
    }
    return std::make_unique<GaussianData>(arguments, calculateData);
};
```

#### Derived class from Model

```cpp
class GaussianModel : public Model<4> {
public:
    GaussianModel() : Model<4>(gaussianFunction) {};

    static std::unique_ptr<Data> gaussianFunction(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters)
    {
        std::vector<double> calculateData;
        calculateData.resize(arguments.size());
        double A = parameters[0], mu = parameters[1], sigma = parameters[2], c = parameters[3];

        for (int i = 0; i < arguments.size(); i++)
        {
            double updatedX = (arguments[i] - mu);
            calculateData[i] = A * exp(-pow(updatedX, 2) / (2 * sigma)) + c;
        }
        return std::make_unique<GaussianData>(arguments, calculateData);
    }
    std::shared_ptr<Data> operator()(const std::vector<double>& arguments, const Parameters<4>& parameters, const AdditionalParameters& additionalParameters) {
        return Model::operator()(arguments, parameters, additionalParameters);
    };
};

```
