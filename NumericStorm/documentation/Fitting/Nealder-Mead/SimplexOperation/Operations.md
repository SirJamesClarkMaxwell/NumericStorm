# ISimplexOperation

```cpp
ISimplexOperation(const std::string& operationName, const SimplexOperationSettings& arguments)
virtual SimplexFigure<parameter_size> operator()(SimplexFigure<parameter_size>& simplexFigure)=0;
void updateSettings(const SimplexOperationSettings& newSettings)
```

All of this operations share the same interface, depicted above. However, what could be interesting is that even if the operation seems to return a single point, the actual returning type is a simplex figure. It is done in this way because the API should be consistent, and we believe that we will not see a huge lost of performance if we firstly calculate all possible steps of the algorithm and in the second step we just pick the appropriate one.

<!--TODO: later change it into void function, and added the reference as the place where a new simplex figure will be stored  -->

<!-- TODO: add the short description of how user might want to extend this module  -->

## SimplexOperationSettings

This class is nothing more than wrapper around the double, later called factor. We decided to do it in this way, because you might want to extend, or modify, default settings of the predefined operations.

The index $x_worst$ mean the worst point in simplexFigure, but `parameter_size` the best

## Reflection

#### Formula

$$ x*{reflected} = centroid + \alpha\*(centroid - x*{worst}) $$

## Expansion

#### Formula

$$ x*{expanded} = centroid + \gamma\*(x*{reflected} - centroid) $$

## Contraction

#### Formula

$x_c$ = point to contraction: better of reflected and the best one
$$ x\_{contracted} = centroid + \gamma\*( x_c- centroid) $$

## Shrinking

#### Formula

$result_i$ is the next point of final simplex, $x_i$ is the existing shrinking point
$$ result_i = x*{best} + \delta\*(x*i - x\*{best}) $$

$x \in [0,parameter\_size - 1]$

# Example usage of the code

Almost everything what you need to extend this part of the library is just implement a new rule of constructing _new_ simplex figure. The only thing that will be required is the returning type, in other case code will not compile.

<!-- TODO: add the reference into the SimplexOperationFactory where will be an example usage of the code declared inside this class -->
