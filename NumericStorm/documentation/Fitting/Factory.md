# General purpose of this module

We want to design the most general fabric, as the one of the design pattern, as it can be in terms of fitting procedure. This **Module** contains only two classes in his abstract implementation. The first class is <span style="color:lightgreen">CreatorInterface </span>, and the second one are <span style="color:lightgreen"> Factory </span>. Both classes are templated, but the true clue of this module is, surprisingly, **CreatorInterface**.

# Creator Interface

An <span style ="color: lightblue"> Abstract</span> <span style="color: lightgreen">Class</span> responsible for forcing some behaviors of derived classes. It is templated by three classes: <span style="color:lightgreen">CreatorInput, CreatorOutput, CreatorSettings</span>. Later in this docs we will call them <span style="color:lightgreen">In, Out, Settings</span>. It is not a holy gral mystery that these classes defines what this concrete creator will produce, and the output of his overridden calling operator. We designed in a way that is easy to extend and change. What we recommend is put all your logic of factory to the `Settings` class. The other recommendation is to override a `updateSettings` method. If your creator needs to set things internally, we suggest to provide an API for this in Settings class, and call every function that will set-up the concrete creator.

# Factory

# Code example
