# Parameters

## General Description
This class is a based class for all Fitting algorithms. In your project you will probably want to create your own Parameter class that will be used this class or inherit from Parameter. All library is designed to deal with both solutions. The only thing that you need to provide is implementing of Parameters <span style = "color:green"> API. </span> 

The Parameters class template provides a simple container for holding a set of parameters and their associated error. It provides methods for retrieving the parameters, their error, and accessing a specific parameter by index.

The template parameter parameter_size determines the number of parameters that can be stored. The member types are value_type, which is an array of doubles with parameter_size elements, and reference, which is a reference to a double in the parameter set. There is also a const_reference, which is a const reference to a double in the parameter set.



## Constructors
```cpp 
Parameters() 
Parameters(std::array<double, parameter_size> parameters): 
```
The **default** constructor, initializes the parameter set to all zeros and sets the error to -1.
Constructs a Parameters object with the specified parameters.
Copy constructor is generated automatically by compiler. 

## member atributes
```cpp
std::array<double, parameter_size> m_parameters
double m_error
```


## Public methods
```cpp 
std::array<double, parameter_size> getParameters() const;
double getError() const;
double& operator[](int index) noexcept;
const double& operator[](int index) const noexcept;
```
Returns the parameters of the object. \
Returns the error associated with the parameters.\
Returns a reference to the parameter at the specified index.\
Returns a const reference to the parameter at the specified index.


# An example usage is:
```cpp
#include "Parameters.hpp"

int main()
{
    // Create a Parameters object with 3 parameters
    std::array<double,3> params ={1.0, 2.0, 3.0};
    Parameters<3> parameters(params); ;

    std::cout << "Parameters: ";
    for (int i = 0; i < 3; i++)
     std::cout << i <<":"<<<<parameters[i]<< " " 
     
    std::cout << std::endl;

    // Get the error
    double error = params.getError();
    std::cout << "Error: " << error << std::endl;

    // Access a parameter by index
    double& param_ref = params[0];
    param_ref = 4.0;
    std::cout << "Parameter 0: " << param_ref << std::endl;

    return 0;
}
```