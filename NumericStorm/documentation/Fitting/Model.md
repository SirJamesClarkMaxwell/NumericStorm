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

Let's go break this out piece by piece:

- the returning value is the unique pointer into <span style = "color: lightblue">abstract</span> <span style = "color: green"> Data</span> class
- <span style ="color: green"> std::vector </span> <<span style = "color: lightblue">double</span></span>> the fist argument is arguments, this is just a set of x's for standard mathematical functions
- <span style = "color: green"> Parameters </span> This is the the object that will be fitted inside the fitter class.
- <span style="color: green"> AdditionalParameters</span> this argument will optional. If function needs any other additional parameters to return correct result this is the right place to store this type of information

All arguments are passed by const reference, because we want to avoid unnecessary copies of this potentially heavy object.

The return type is a unique pointer because we don't want to return data by value. This will potentially be a heavy item. Moreover, we don't particularly want to have multiple pointers to the same block of memory -> unique pointers arrived.

One more addition to this description of class, because this is the abstract class you need to implement the calling operator. And also you need to implement the concrete <span style="color:green"> Data </span> class by inheriting from it.
