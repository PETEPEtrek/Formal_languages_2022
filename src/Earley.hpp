#pragma once

#include <string>
#include <vector>
#include <set>
#include "Situation.hpp"
#include "Grammar.hpp"
#include "gtest/gtest.h"

class Earley {
private:
    Grammar grammar_;

    FRIEND_TEST(Earley, checkScan);
    void Scan(int32_t j, std::string w);

    FRIEND_TEST(Earley, checkPredict);
    void Predict(int32_t j);

    FRIEND_TEST(Earley, checkComplete);
    void Complete(int32_t j);

public:
    explicit Earley(Grammar& grammar) : grammar_(grammar) {}

    bool EarleyParse(std::string word);

    Grammar& GetGrammar() {
        return grammar_;
    }
};
