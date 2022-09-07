#include "mealy/mealy.hpp"
#include <iostream>
#include <string>
int main(int argc, char *argv[])
{
    mealy<int, std::string, std::string> dfa(0, "state map undefined");
    for (int i = 0; i < 5; i++) {
        dfa.addState(i);
    }

    // std::function<int(std::string)> testFunc = [](int) -> std::string {
    //     return "1";
    // }
    dfa.setMapping(
        0, [](std::string input) -> int { return 1; },
        [](std::string input) {
            return "with input " + input + ", moved from 0 to 1";
        });

    std::cout << dfa.transition("hello") << '\n';
    bool success;

    // try removing initstate
    success = dfa.rmState(0);
    std::cout << "removed state 0: " << success << '\n';
    // try removing a nonexistent state
    success = dfa.rmState(-1);
    std::cout << "removed state -1: " << success << '\n';
    // try changing init state to a nonexistent value
    success = dfa.initState(-1);
    std::cout << "changed init state to -1: " << success << '\n';
    // change the init state
    success = dfa.initState(1);
    std::cout << "changed init state to 1: " << success << '\n';
    // remove a state
    success = dfa.rmState(0);
    std::cout << "removed state 0: " << success << '\n';
    success = dfa.setMapping(
        0, [](std::string input) -> int { return 1; },
        [](std::string input) {
            return "with input " + input + ", moved from 0 to 1";
        });
    std::cout << "mapped to nonexistent state: " << success << '\n';
    return 0;
}
