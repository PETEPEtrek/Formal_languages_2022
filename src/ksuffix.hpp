#pragma once
#include <unordered_map>
#include <unordered_set>
#include <stack>

class KSuffix {
private:
    using Lengths = std::unordered_set<int64_t>;
    using States = std::unordered_map<int64_t, Lengths>;
    std::string backPolishNotation;
    char x;
    int64_t k;
public:
    KSuffix(std::string& backPN, char& letter, int64_t& k): backPolishNotation(backPN), x(letter), k(k) {}
    bool isCorrectSymbol(char symbol);
    std::string FindLenOfKSuffix();
};

