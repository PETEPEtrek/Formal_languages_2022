//
// Created by Acer on 05.10.2022.
//

#include "ksuffix.hpp"

void KSuffix::PlusCase(std::stack<States>& states) {
    auto first_elem = states.top();
    states.pop();
    auto second_elem = states.top();
    states.pop();
    States result{};
    for (auto& state: first_elem) {
        for (auto& word_length: state.second) {
            result[state.first].emplace(word_length);
        }
    }
    for (auto& state: second_elem) {
        for (auto& word_length: state.second) {
            result[state.first].emplace(word_length);
        }
    }
    states.push(result);
}

void KSuffix::ConcatCase(std::stack<States>& states) {
    auto first_elem = states.top();
    states.pop();
    auto second_elem = states.top();
    states.pop();
    States result{};
    for (auto& state: second_elem) {
        for (auto& word_first: state.second) {
            for (auto& state_second: first_elem) {
                for (auto& word_second: state_second.second) {
                    if (state_second.first == word_second) {
                        result[state.first + state_second.first].emplace(word_first + word_second);
                    } else {
                        result[state_second.first].emplace(word_second + word_first);
                    }
                }
            }
        }
    }
    states.push(result);
}
void KSuffix::KleeneStarCase(std::stack<States>& states) {
    states.top()[0].emplace(0);
    for (auto& state: states.top()) {
        if (state.first == 0) {
            continue;
        }
        if (state.second.count(state.first)) {
            int64_t multiplier = 2;
            while (multiplier * state.first <= k) {
                states.top()[multiplier * state.first].emplace(multiplier * state.first);
                multiplier++;
            }
        }
    }
}


std::string KSuffix::FindLenOfKSuffix() {
    std::stack<States> states;
    for (auto& symbol: backPolishNotation) {
        if (!isCorrectSymbol(symbol)) {
            return "Bad Notation: bad symbols!";
        }
        if (symbol >= 'a' && symbol <= 'c') {
            if (symbol == x) {
                states.push(States{{1, {1}}});
            } else {
                states.push(States{{0, {1}}});
            }
        } else if (symbol == '1') {
            states.push(States{{0, {0}}});
        } else if (symbol == '*') {
            if (states.empty()) {
                return "Bad Notation: not enough operands in notation for *";
            }
            KleeneStarCase(states);

        } else if (symbol == '+') {
            if (states.size() < 2) {
                return "Bad Notation: not enough operands in notation for +";
            }
            PlusCase(states);

        } else if (symbol == '.') {
            if (states.size() < 2) {
                return "Bad Notation: not enough operands in notation for .";
            }
            ConcatCase(states);

        }
    }
    if (states.size() > 1) {
        return "Bad Notation: stack is not empty!";
    }
    if (states.top()[k].empty()) {
        return "INF";
    } else {
        int64_t min = std::numeric_limits<int64_t>::max();
        for (const auto& length: states.top()[k]) {
            if (length < min) {
                min = length;
            }
        }
        return std::to_string(min);
    }
}
bool KSuffix::isCorrectSymbol(char symbol) {
    std::string symbols = "abc1.+*";
    if (symbols.find(symbol) != std::string::npos) {
        return true;
    }
    return false;
}
