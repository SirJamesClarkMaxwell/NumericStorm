#### General Description of the Model Class

This class is responsible for holding information about the function that will calculate the data needed to evaluate the goal function in the fitting procedure. This is achieved using <span style = "color:green">std::function<> </span>.

#### template arguments

1. <span style = "color:green"> size_t </span> parameter_size
2. <span style="color: lightblue"> class</span></span><span style = "color:green"> AuxilaryParameters </span> = <span style = "color:green"> AdditionalParameters</span>
3.

Let's explain how this class is working.

First of all this is a concrete class. The `parameter_size` template argument is responsible for determining the array size, that is stored inside the Parameter class.
Why we used the std::array instead of the std::vector, check the `Parameters` documentation page.

The `AdditionalParameters` reason is a little bit more complicated. We decided to use the template argument instead of the abstract class `AdditionalParameters`, because we are not be able to write a class responsible for holding all possible combinations of additional parameters, and provide the methods for setting and getting this auxiliary parameters.
The way how this is working: You have to implement your own class and pass it as the template argument into the derived model class. In your method that will evaluate the data (this is described more detail in the next paragraph) you could do what ever you want with your derived AdditionalParameters.

#### How to make my own Model class

What we are suggesting here is that you should inherit from the Model class, instead defining a std::function object in code and pass it into the constructor. In derived class add the static [^1] and pass it as the argument into the initializer list as it is
done in the example code below.

[^1]: this is really important that this method should be static in other case the code will not compile, it could be private it doesn't matter

### Constructor and overloaded () operator:

What we suggest is this type of alias for the type of argument passed into the constructor, and

```cpp
template<size_t parameter_size, class AuxilaryParameters = AdditionalParameters>
using ModelFunctionType = std::function<void(Data&, const Parameters<parameter_size>&, const AuxilaryParameters&)>;
Model(const ModelFunctionType& model);

void operator()(Data& data, const Parameters<parameter_size>& parameters, const AuxilaryParameters& additionalParameters)
```

Let's go break this out piece by piece:

1.  We are not returning any thing from overloaded calling operator, all calculated data should be inject into data object. This is a reason why we decided to pass this object as reference instead of const reference.
2.  <span style = "color: green"> Data </span> is a wrapper for multi-dimensional vector. To get more details, see the `Data` documentation page.
3.  <span style = "color: green"> Parameter </span> is the object that stores the evaluating parameters.
4.  <span style = "color: green"> AuxilaryParameters</span>, in reality it is a <span style = "color: green">AdditionalParameters</span>. It was named in this way, because we wanted to avoid naming problems.

### Example of usage

<!---
All code of declared function will be available in the end of this file, in table of context it will marked as the `Full Code`
This class could be used in in two different ways:

1. By a roll classes
2. By derived classes

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
--->
