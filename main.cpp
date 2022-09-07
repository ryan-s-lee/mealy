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

    std::cout << dfa.transition("hello");
    return 0;
}
