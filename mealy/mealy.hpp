#ifndef RYOLOGY_MEALY_H
#define RYOLOGY_MEALY_H

#include <functional>
#include <set>
#include <unordered_map>
#include <utility>

template <typename T, typename K, typename V> class mealy
{
  private:
    T _currentState;
    T _initState;
    V _undefMapOut;
    std::set<T> _states;
    std::unordered_map<T, std::pair<std::function<T(K)>, std::function<V(K)>>>
        _stateToTransMap;

  public:
    mealy(T initState, V noMapErrResult);
    inline void addState(T state);
    inline bool rmState(T state);
    inline bool setMapping(T state, std::function<T(K)> toMap,
                           std::function<V(K)> outMap);
    inline bool rmMapping(T state);
    inline V transition(K input);
    inline T initState() {
        return _initState;
    }
    inline bool initState(T state);

    V undefMapOut() {
        return _undefMapOut;
    }
    V undefMapOut(V replace) {
        V oldValue = _undefMapOut;
        _undefMapOut == replace;
        return _undefMapOut;
    }
};

template <typename T, typename K, typename V>
mealy<T, K, V>::mealy(T initState, V noMapErrResult)
    : _initState(initState), _currentState(initState), _states{_initState},
      _undefMapOut(noMapErrResult)
{
}

template <typename T, typename K, typename V>
void mealy<T, K, V>::addState(T state)
{
    _states.insert(state);
}

template <typename T, typename K, typename V>
bool mealy<T, K, V>::rmState(T state)
{
    auto result = _states.find(state);
    if (result == _states.cend() || *result == _initState) {
        return false;
    }
    _states.erase(result);
    return true;
}

template <typename T, typename K, typename V>
bool mealy<T, K, V>::setMapping(T state, std::function<T(K)> toMap,
                                std::function<V(K)> outMap)
{
    if (_states.find(state) == _states.cend()) {
        return false;
    }
    _stateToTransMap.insert_or_assign(
        state,
        std::pair<std::function<T(K)>, std::function<V(K)>>(toMap, outMap));
    return true;
}

template <typename T, typename K, typename V>
bool mealy<T, K, V>::rmMapping(T state)
{
    auto result = _stateToTransMap.find(state);
    if (result == _stateToTransMap.cend()) {
        return false;
    }
    _stateToTransMap.erase(result);
    return true;
}

template <typename T, typename K, typename V>
V mealy<T, K, V>::transition(K input)
{
    auto mapResult = _stateToTransMap.find(_currentState);
    if (mapResult == _stateToTransMap.cend()) {
        _currentState = _initState;
        return _undefMapOut;
    }
    int nextState = (mapResult->second.first)(input);
    if (_states.find(nextState) == _states.cend()) {
        _currentState = _initState;
    } else {
        _currentState = nextState;
    }
    return (mapResult->second.second)(input);
}

template <typename T, typename K, typename V>
bool mealy<T, K, V>::initState(T state)
{
    auto result = _states.find(state);
    if (result == _states.end()) {
        return false;
    }
    _initState = result;
    return true;
}

#endif
