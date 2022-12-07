#include "Grammar.hpp"


void Grammar::AddRule(char A, std::string& alpha) {
    rules_.emplace_back(A, alpha);
}

void Grammar::AddRule(char A, std::string&& alpha) {
    rules_.emplace_back(A, alpha);
}

void Grammar::AddSituations(int32_t i, Situation&& situation) {
    D_[i].insert(situation);
}

std::vector<std::pair<char, std::string>>& Grammar::GetRules() {
    return rules_;
}

std::vector<std::set<Situation>>& Grammar::GetSituations() {
    return D_;
}

void Grammar::ClearGrammar(std::string& word) {
    D_.clear();
    D_.resize(word.length() + 1);
}