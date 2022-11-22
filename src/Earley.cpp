#include "Earley.hpp"


void Earley::Scan(int32_t j, std::string w) {
    if (j == 0) {
        return;
    }
    for (const auto& situation: grammar_.GetSituations()[j - 1]) {
        if (w[j - 1] == situation.GetBeta()[0]) {
            auto cur_situation = Situation{situation.GetA(), situation.GetAlpha() + w[j - 1],
                                           situation.GetBeta().substr(1,
                                                                      situation.GetBeta().size()), situation.GetI()};
            grammar_.AddSituations(j, cur_situation);
        }
    }
}

void Earley::Complete(int32_t j) {
    for (const auto& empty_beta_situation: grammar_.GetSituations()[j]) {
        if (!empty_beta_situation.GetBeta().empty()) {
            continue;
        }
        for (const auto& situation: grammar_.GetSituations()[empty_beta_situation.GetI()]) {
            if (empty_beta_situation.GetA() != situation.GetBeta()[0]) {
                continue;
            }
            auto cur_situation = Situation{situation.GetA(), situation.GetAlpha() + empty_beta_situation.GetA(),
                                           situation.GetBeta().substr(1,
                                                                      situation.GetBeta().size()), situation.GetI()};
            grammar_.AddSituations(j, cur_situation);
        }
    }
}

void Earley::Predict(int32_t j) {
    for (const auto& situation: grammar_.GetSituations()[j]) {
        for (const auto& rule: grammar_.GetRules()) {
            if (rule.first == situation.GetBeta()[0]) {
                auto cur_situation = Situation{rule.first, "",
                                               rule.second, j};
                grammar_.AddSituations(j, cur_situation);
            }
        }
    }
}

bool Earley::EarleyParse(std::string word) {
    grammar_.ClearGrammar();
    auto cur_situation = Situation{'0', "",
                                   "S", 0};
    grammar_.AddSituations(0, cur_situation);

    for (int32_t j = 0; j < word.length(); ++j) {
        Scan(j, word);
        auto D_j_size = static_cast<int32_t>(grammar_.GetSituations()[j].size());
        while (true) {
            Complete(j);
            Predict(j);
            if (D_j_size == static_cast<int32_t>(grammar_.GetSituations()[j].size())) {
                break;
            }
            D_j_size = static_cast<int32_t>(grammar_.GetSituations()[j].size());
        }
    }
    if (grammar_.GetSituations()[static_cast<int32_t>(word.length())].count({'0', "S", "", 0})) {
        return true;
    }
    return false;
}