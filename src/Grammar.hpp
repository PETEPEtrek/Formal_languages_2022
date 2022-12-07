#pragma once
#include <vector>
#include <set>
#include "Situation.hpp"

class Grammar {
private:
    using Rule = std::pair<char, std::string>;
    std::vector<Rule> rules_;
    std::vector<std::set<Situation>> D_;

public:
    Grammar() = default;

    explicit Grammar(std::string& word) {
        D_.resize(word.length() + 1);
    }

    explicit Grammar(std::string&& word) {
        D_.resize(word.length() + 1);
    }

    void AddRule(char A, std::string& alpha);
    void AddRule(char A, std::string&& alpha);

    void AddSituations(int32_t i, Situation&& situation);

    std::vector<Rule>& GetRules();

    std::vector<std::set<Situation>>& GetSituations();

    void ClearGrammar(std::string& word);
};
