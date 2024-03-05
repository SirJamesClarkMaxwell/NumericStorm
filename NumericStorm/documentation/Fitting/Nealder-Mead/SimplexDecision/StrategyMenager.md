This class enables users to dynamically modify the Simplex algorithm's behavior, offering more flexibility than conventional setups. Users can define their own algorithms, accommodating variations like Simulated Annealing. This flexibility is achieved by allowing users to create objects that make external decisions and register these objects using std::unique_ptr. The strategy can then be executed by passing a vector of simplex figures to these externally defined decision-making objects.# Strategy Manager

## General Description

This class enables users to dynamically modify the Simplex algorithm's behavior, offering more flexibility than conventional setups. This flexibility is achieved by allowing users to create objects that make external decisions and register these objects using `std::unique_ptr`. The strategy can then be executed by passing a vector of simplex figures to these externally defined decision-making objects.

### Methods

```cpp

void registerStrategy(std::string name, std::unique_ptr<IDecision<parameter_size>> strategy);
void unregisterStrategy(std::string name);
SimplexFigure<paramater_size> makeDecision(std::string name) throw(NoAvailableStrategyException);
```
