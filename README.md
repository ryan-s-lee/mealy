# Nondeterministic Mealy Machine

## Summary
General implementation of a mealy machine in C++. Allow for any type to be used as the state, input, and output. Tested for C++17.

## Use
### Conceptualiztion
All `mealy` objects have a set of states, and an initial state that cannot be removed (unless it the initial state is set to something else). At any given time a `mealy` has a current state. 

### Functions
`void addState(T state)`: Add a new state to the set of possible states. Adding an existing state should do nothing.

`bool rmState(T state)`: Remove a state and its mapping to other states, unless it is the initial state or if it doesn't exist in the machine's set of existing states. Returns true if it removed something, and false if not. 

`bool setMapping(T state, std::function<T(K)> toMap, 
    std::function<V(K)> outMap)`: 
Assigns two functions to `state`, which together represent `state`'s mapping to other states. The first should take an input parameter and outputs another state. This function does NOT need to guarantee that its return value is in the set of existing states (see `transition(K input)` for information on how `mealy` treats states not in its set). The second function determines the output value of any transitions. If the state does not exist, `setMapping` does not assign anything and returns false. Returns true if succesful. 

`bool rmMapping(T state)`: Removes a state's mapping to other states. Note that this removes ALL mappings; if you want to remove just one, this involves replacing the mapping with a new function using `setMapping`. 

`T initState()`: Returns the value of the initial state. 

`bool initState(T state)`: Attempts to change the value of the initial state. If the state is not in the machine's set of states, the function does not change the state and returns false. Otherwise, performs the change and returns true.

`V transition(K input)`: Change the current state of the machine to one determined from inputting `input` to its associated transition function. If the transition function outputs a non-existent state, or if no mapping exists for the current state, returns `undefMapOut()` and sets the state to the initial state. 

`V undefMapOut()`: Returns the value that would be returned by `transition` if the transition function gets an illegal next state, or if the current state does not have a defined mapping. 

`V undefMapOut(V replace)`: Sets `undefMapOut()` to `replace` and returns its old value. 

## Remarks
This implementation is technically not a true Mealy machine. It is possible to map one input to multiple states (e.g. via a random number generator). Also, its input and output alphabets are not explicitly finite; they are only bounded by type and hardware limitations. However, I find it a practical implementation as it is small and flexible. For example, assigning mappings for ranges of inputs can be as simple as using comparison operators in the transition and output functions. 

I believe that it is relatively easy for this machine to exhibit practical mealy machine behavior; the main condition is that all functions that map their state to others are well-defined.

