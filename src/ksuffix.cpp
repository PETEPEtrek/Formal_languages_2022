//
// Created by Acer on 05.10.2022.
//

#include "ksuffix.hpp"
std::string KSuffix::FindLenOfKSuffix() {
    std::stack<States> states;
    for (auto& symbol: backPolishNotation) {
        if (!isCorrectSymbol(symbol)) {
            return "Bad Notation: bad symbols!";
        }
        if (symbol >= 'a' && symbol <= 'c') {
            if (symbol == x) {
                states.push(States{1, 1});
            } else {
                states.push(States{0, 1});
            }
        } else if (symbol == '1') {
            states.push(States{0, 0});
        } else if (symbol == '*') {
            if (states.empty()) {
                return "Bad Notation: not enough operands in notation for *";
            }
            if (states.top().count(0) == 0) {
                states.top()[0] = {0};
            }
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
        } else if (symbol == '+') {
            if (states.size() < 2) {
                return "Bad Notation: not enough operands in notation for +";
            }
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
        } else if (symbol == '.') {
            if (states.size() < 2) {
                return "Bad Notation: not enough operands in notation for +";
            }
            auto first_elem = states.top();
            states.pop();
            auto second_elem = states.top();
            states.pop();
            States result{};
            
        }
    }
    return std::string();
}
bool KSuffix::isCorrectSymbol(char symbol) {
    std::string symbols = "abc1.+*";
    if (symbols.find(symbol) != std::string::npos) {
        return true;
    }
    return false;
}
