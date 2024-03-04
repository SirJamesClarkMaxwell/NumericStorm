# Brief Explanation of the Abstract SimplexFitter Class

## The class diagram
```mermaid
classDiagram
class Fitter{
    <<abstract>>
    # Parameters~n~ m_fittedParameters
    # Parameters~n~ m_proposedParameters
}
Fitter: + abstract minimize()
class SimplexFitter{
    <<abstract>>
    # SimplexFigure~n~ m_simplexFigure
    # SimplexCreatorFactory m_simplexCreatorFactory
    # SimplexDecider m_simplexDecider

}
Fitter <|.. SimplexFitter
```

## Simple explanation of the abstract SimplexFitter class
[About the General Simplex Algorithm](https://nils-olovsson.se/articles/downhill_simplex/#citation-crane)  
This abstract class serves as a blueprint for future implementations of Simplex optimization solvers. It is designed to allow users to define their own implementations of the Simplex optimization technique.

### The main idea
To ensure maximum flexibility, we have incorporated the factory design pattern extensively throughout this class. This approach enables us to extract functionality and facilitate easy customization.

