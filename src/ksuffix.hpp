#pragma once
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <iostream>
#include <utility>
#include "gtest/gtest.h"



class KSuffix {
private:
    using Lengths = std::unordered_set<int64_t>;
    using States = std::unordered_map<int64_t, Lengths>;
    std::string backPolishNotation;
    char x;
    int64_t k;

    FRIEND_TEST(KSuffix, checkPlus);
    void PlusCase(std::stack<States>& states);

    FRIEND_TEST(KSuffix, checkConcat);
    void ConcatCase(std::stack<States>& states);

    FRIEND_TEST(KSuffix, checkKleeneStarCase);
    void KleeneStarCase(std::stack<States>& states);

    FRIEND_TEST(KSuffix, checkSymbols);
    bool isCorrectSymbol(char symbol);
public:
    KSuffix(std::string& backPN, char& letter, int64_t& k): backPolishNotation(backPN), x(letter), k(k) {}
    void ChangeK(int64_t new_k) {
        k = new_k;
    }
    void ChangeX(char new_x) {
        x = new_x;
    }
    void ChangeNotation(std::string new_notation) {
        backPolishNotation = std::move(new_notation);
    }
    std::string FindLenOfKSuffix();
};

