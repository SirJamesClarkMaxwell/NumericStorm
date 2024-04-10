# General purpose of this module

We want to design the most general fabric, as the one of the design pattern, as it can be in terms of fitting procedure. This **Module** contains only two classes in his abstract implementation. The first class is <span style="color:lightgreen">CreatorInterface </span>, and the second one are <span style="color:lightgreen"> Factory </span>. Both classes are templated, but the true clue of this module is, surprisingly, **CreatorInterface**.

# Creator Interface

An <span style ="color: lightblue"> Abstract</span> <span style="color: lightgreen">Class</span> responsible for forcing some behaviors of derived classes. It is templated by three classes: <span style="color:lightgreen">CreatorInput, CreatorOutput, CreatorSettings</span>. Later in this docs we will call them <span style="color:lightgreen">In, Out, Settings</span>. It is not a holy gral mystery that these classes defines what this concrete creator will produce, and the output of his overridden calling operator. We designed in a way that is easy to extend and change. What we recommend is put all your logic of factory to the `Settings` class. The other recommendation is to override a `setUp` method. If your creator needs to set things internally, we suggest to provide an API for this in Settings class, and call every function that will set-up the concrete creator. Because `setUp` method doesn't return anything, we suggest to use a member variables, you need to remember that this functionality should be implemented in the lowest possible level, it mean that you will have access to the concrete objects.

# Creator SetUp Info

Before we proceed to the main content of this documentation page, it's important to discuss the <span style="color: lightgreen">CreatorSetUpInfo</span> class. This class is templated by the <span style="color: lightgreen">Settings</span> from the `Settings` class, which you must define. Additionally, the `Settings` class used here must be the same class passed into the template arguments of the `Creator`. We introduced the <span style="color: lightgreen">CreatorSetUpInfo</span> struct to avoid passing two vectors directly into the function that registers creators and to streamline their updates.

# Factory

First things first, this class is our implementation of [Factory Patter](https://refactoring.guru/design-patterns/factory-method) combined with [Template Method](https://refactoring.guru/design-patterns/template-method) and [Strategy Pattern](https://refactoring.guru/design-patterns/strategy) but we extend it to be more generic and easy to use.

In the next part of docs, we assume that you got the idea of these designed patterns.

## API

Important note: Code below will not compile, apart from that defined types are abstract, we decided to use a syntactic sugar <!--  I hope that this is a correct name what i have done bellow--> to simplify and make easy to read and analyze the API.

```cpp
void registerCreator(const std::vector<CreatorSetUpInfo<Creator::Settings>>& settings);
Creator::Out invoke(const std::string& name, const Creator::In& input);
void updateSettings(const std::vector<CreatorSetUpInfo<Creator::Settings>>& newSettings);
void deleteCreator(const std::string& name);
Factory<Creator>();
```

## Explanation

To use this class, apart form that you have to make an instance of it, follow the next algorithm:

1.  Define your own <span style = "color: lightgreen">Creator</span> class, templated by his own classes
2.  Instantiate a vector of <span style = "color:lightgreen">CreatorSetUpInfo</span>
    1. Create roll objects of your Settings, related to the `Creator` that you want to use
    2. create a strings associated with those settings.
    3. "Bind" them into struct <span style = "color:lightgreen">CreatorSetUpInfo</span>
3.  Crate a vector of <span style = "color:lightgreen">CreatorSetUpInfo</span> objects
4.  Pass them into <span style = "color:yellow">registerCreators</span> method.
5.  <span style = "color:red">DON'T FORGET</span> to add the LISTS of templated arguments

```cpp
std::vector<YourAbstractCreator::YourSettings> yourSettingsVector;
InPutType input;
Factory<YourAbstractCreator> yourFactory;
yourFactory.registerFactor<Creator1,Creator2,Creator3>(yourSettingsVector);
OutPutType outPut = yourFactory.invoke("name_of_your_creator", input);
```

From user point of view, this is everything what you need to know to use it.

## Private Methods Explained in really detailed way

If you want to understand and extend this code this section would be very helpful.

Recap of public method for registering creators

```cpp
template <class ... Creators>
void registerCreator(const std::vector<CreatorSetUpInfo<Creator::Settings>>& settings);
```

#### List of private methods

```cpp
template<class CurrentCreator, class NextCreator, class ...RestCreators>
void registerCreators(int position, std::vector<CreatorSetUpInfo<typename Creator::Settings>>& settingsVector)
template<class NextCreator>
void registerCreators(int position, std::vector<typename Creator::Settings >> settingsVector)
void registerCreator(const std::string& creatorName, const Creator& instance);
template<class DerivedCreator>
void registerOneCreator(const CreatorSetUpInfo<typename Creator::Settings>& creatorSetUpInfo)
bool checkIfAvailable(const std::string& creatorName) const
```

What you could notice is that there are two functions with the same name, but different templates arguments. In public function, only what we are doing is invoking the private function `registerCreators`. Inside the private registerCreators method we are registering one creator (`registerOneCreator`) and call again the same function but with decreased number of variadic template arguments. The last method called `registerCreators` (with only one template argument) is responsible for holding the edge case if there are left only one creator to register. What could be helpful to understand this code is to check the call stack, or run this code in DEBUG mode, and follow the function calling. If you have any question related to this class, please make an issue on GitHub, or write on my email address: <!--todo later paste our email address-->

# Code example
