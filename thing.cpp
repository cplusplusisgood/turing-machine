#include <array>
#include <iostream>
#include <vector>

struct state {
    state* nextstates[2] = {nullptr, nullptr}; // nullptr means halt
    bool nextsymbol[2] = {false, false};       // symbol to write
    bool direction[2] = {false, false};        // true = right, false = left
};

int main() {
    constexpr int TAPE_LEN = 4096;
    constexpr int START_POSITION = TAPE_LEN / 2;

    std::array<bool, TAPE_LEN> tape{}; // initially all zeros
    std::vector<state> states(2);

    // Example machine:
    // State 0: on 0, write 1, move right, go to state 1.
    // On 1, halt.
    states[0].nextstates[0] = &states[1];
    states[0].nextsymbol[0] = true;
    states[0].direction[0] = true;

    // State 1: on 0, write 0, move left, go to state 0.
    // On 1, halt.
    states[1].nextstates[0] = &states[0];
    states[1].nextsymbol[0] = false;
    states[1].direction[0] = false;

    int currentNode = START_POSITION;
    state* currentState = &states[0];

    while (true) {
        if (currentNode < 0 || currentNode >= TAPE_LEN) {
            std::cerr << "Error: tape head moved outside the tape.\n";
            return 1;
        }

        int symbol = tape[currentNode] ? 1 : 0;
        state* nextState = currentState->nextstates[symbol];

        if (nextState == nullptr) {
            break; // halt
        }

        tape[currentNode] = currentState->nextsymbol[symbol];
        currentNode += currentState->direction[symbol] ? 1 : -1;
        currentState = nextState;
    }

    std::cout << "Halted. Tape around starting position:\n";
    for (int i = START_POSITION - 5; i <= START_POSITION + 5; ++i) {
        std::cout << (tape[i] ? '1' : '0');
    }
    std::cout << '\n';

    return 0;
}
