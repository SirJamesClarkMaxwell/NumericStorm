# Parameters

## General Description

This class is a base class for all fitting algorithms. In your project, you may want to create your own Parameter class that inherits from this class or uses this class as a base. The library is designed to work with both solutions. The only thing you need to provide is the implementation of the Parameters API.

The Parameters class template provides a simple container for holding a set of parameters. It provides methods for retrieving the parameter and accessing a specific parameter by index.

The template parameter `parameter_size` determines the number of parameters that can be stored. The member types are:

- `value_type`: an array of doubles with `parameter_size` elements
- `reference`: a reference to a double in the parameter set
- `const_reference`: a const reference to a double in the parameter set

## Important information

If the `parameter_size` will be different than number of elements passed to the `std::initializer_list` you will get an exception! The size must be matched.

## API

```cpp
Parameters(const std::array<double, parameter_size>& parameters);
Parameters(std::initializer_list<double>& parameters);
virtual std::array<double, parameter_size>& getParameters() ;
```

Apart of listed methods this class also has default implementations of:

- copy and move constructor
- copy and move assignment operator
- const version of index operator and `getParameters` methods

### Member attributes

```cpp
std::array<double, parameter_size> m_parameters;
```

# An example usage is:

```cpp
#include "Parameters.hpp"

int main()
{
    // Create a Parameters object with 3 parameters
    std::array<double, 4> referencedArray{ 2, 1, 2, -1 };
    Parameters<4> referencedParameters{ referencedArray };

    Parameters<3> parameters2({1.0, 2.0, 3.0});
    std::cout << "Parameters: ";

    for (int i = 0; i < 3; i++)
        std::cout << i << ":" << parameters[i] << " ";
    std::cout << std::endl;

    for (int i = 0; i < 3; i++)
        std::cout << i << ":" << parameters2[i] << " ";
    std::cout << std::endl;

    // Access a parameter by index
    double& param_ref = parameters[0];
    param_ref = 4.0;
    std::cout << "Parameter 0: " << param_ref << std::endl;

    return 0;
}
```
