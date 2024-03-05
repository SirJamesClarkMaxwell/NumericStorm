# IDecision

## The general purpose of this class

The goal of this class is to provide a simple way of implementing the logic behind the simplex algorithm and his modifications, including or removing some operation, and defining your own implementation of standard Simplex algorithms.

```cpp
virtual SimplexFigure<parameter_size> makeDecision(const std::vector<SimplexFigure<parameter_size>>& simplexFigures) = 0;
```

### Our advice

If you are fluent in programming in C++, you could skip this part of documentation.
If not this could help you to write a better code.

#### We recommend

- To use the `enum`, or in more secure version of the code `enum class`, in classes inheriting form **IDecision**. It will prevent you from hard-coding indexes in `makeDecision` method.
- Using the `std::out_of_range` exception in `makeDecision` method
