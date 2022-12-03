#include "Earley.hpp"

void Earley::Scan(int32_t j, std::string w) {
    if (j == 0) {
        return;
    }
    for (const auto& situation: grammar_.GetSituations()[j - 1]) {
        if (w[j - 1] == situation.GetBeta()[0]) {

            grammar_.AddSituations(j, Situation{situation.GetA(), situation.GetAlpha() + w[j - 1],
                                                situation.GetBeta().substr(1), situation.GetI()});
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

            grammar_.AddSituations(j, Situation{situation.GetA(), situation.GetAlpha() + empty_beta_situation.GetA(),
                                                situation.GetBeta().substr(1), situation.GetI()});
        }

    }
}

void Earley::Predict(int32_t j) {
    for (const auto& situation: grammar_.GetSituations()[j]) {

        for (const auto& rule: grammar_.GetRules()) {

            if (rule.first == situation.GetBeta()[0]) {

                grammar_.AddSituations(j, Situation{rule.first, "",
                                                    rule.second, j});
            }

        }

    }
}

bool Earley::EarleyParse(std::string word) {
    grammar_.ClearGrammar(word);

    grammar_.AddSituations(0, Situation{'0', "",
                                        "S", 0});

    for (int32_t j = 0; j <= word.length(); ++j) {
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
    for (auto& situation: grammar_.GetSituations()[static_cast<int32_t>(word.length())]) {
        if ((Situation) situation == Situation{'0', "S", "", 0}) {
            return true;
        }
    }

    return false;
}