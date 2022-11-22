#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

class Situation {
private:
    char A_;
    std::string alpha_;
    std::string beta_;
    int32_t i_;

public:
    Situation(char A, std::string alpha, std::string beta, int32_t i) : A_(A), alpha_(std::move(alpha)), beta_(std::move(beta)), i_(i) {}

    int32_t GetI() const {
        return i_;
    }

    char GetA() const {
        return A_;
    }

    std::string GetAlpha() const {
        return alpha_;
    }

    std::string GetBeta() const {
        return beta_;
    }
};

class Grammar {
private:
    std::unordered_set<std::pair<char, std::string>> rules_;
    std::unordered_map<int32_t, std::unordered_set<Situation>> D_;

public:
    Grammar() = default;

    void AddRule(char A, std::string& alpha) {
        rules_.insert({A, alpha});
    }

    void AddSituations(int32_t i, Situation& situation) {
        D_[i].insert(situation);
    }

    std::unordered_set<std::pair<char, std::string>>& GetRules() {
        return rules_;
    }

    std::unordered_map<int32_t, std::unordered_set<Situation>>& GetSituations() {
        return D_;
    }

    void ClearGrammar() {
        D_.clear();
   }
};

class Earley {
private:
    Grammar grammar_;
    void Scan(int32_t j, std::string w);
    void Predict(int32_t j);
    void Complete(int32_t j);

public:
    Earley(Grammar& grammar) : grammar_(grammar){}

    bool EarleyParse(std::string word);

    Grammar& GetGrammar() {
        return grammar_;
    }
};
