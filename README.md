![DALL·E 2024-03-01 21 56 33 - Create a simple yet impactful 2D digital artwork featuring a glowing blue lightning bolt, symbolizing the power and speed of C++ in numeric computatio](https://github.com/SirJamesClarkMaxwell/NumericStorm/assets/71722499/31204663-62af-4240-a711-f1a91f8cdc24)


This is a numerical library written in modern C++. It will be developed as part of the [Semiconductor Studio](https://github.com/SirJamesClarkMaxwell/SemiconductorStudio) project. Now, we are working on the fitting module, precisely the Nelder-Mead optimization technique, also called the Downhill Simplex method. 
The most recent version of the code is in the [**Fitting-Refactoring**](https://github.com/SirJamesClarkMaxwell/NumericStorm/tree/Fitting-Refactoring) branch. Now, we are in refactoring/testing part of the existing code. The documentation can be found on [**Fitting**]([https://github.com/SirJamesClarkMaxwell/NumericStorm/tree/Fitting](https://github.com/SirJamesClarkMaxwell/NumericStorm/tree/Fitting/NumericStorm/documentation/Fitting) branch. When we finish a small part of the tests, we will update the docs, describe in more detail how this module will work, and provide some snippets of usage code. 

### **Existing Code will not compile! We are in the middle of refactoring process and changing the API.**
To get things working, you must have a **Windows** operating system and Visual Studio installed. To run anything, you should follow the next steps:
  - navigate into --vendor-- directory and run **build.py** OR **vendor-premake.bat** script. It will generate a static library for testing (GTest)
  - go back into the leading directory and run **build.py** or **Premake-poligon.bat**
  - finally, run a solution file generated by premake.

The support for the Linuks distribution is planned. We can't estimate when it will be available, but this is our first goal after stabilizing the library. In the library's following `release,` we will add a bat and sh file to set everything up automatically. 

Next, we will work on the multivariate Newtown method, the Greatest Descent method, and the Levemberg-Marquardt optimization technique.
