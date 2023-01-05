#include "Earley.hpp"
/**
 * Function for reading a letter in Situations `beta` part and adding new rules in the next
 * situations set
 * @param j - position of situations set
 * @param w - word that we are parsing
 */
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


/**
 * Function for adding a new situations from `parent` situation set based on a situations with
 * empty  `beta` part, their `i` parameter and S(i) situations where first element of its `beta` part
 * is the `A` part of the situation from S(j). We add a situation with read `A` part, i.e. adding it to the `alpha`
 * part of the situation
 * @param j - position of situation set
 */
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


/**
 *  Function for adding a new situations based on the first element of `beta` part of the current situation
 *  and the left part of the current rule : we add a new situation if they are the same
 * @param j - position of the situations set
 */
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

/**
 *
 * @param word - word that we parse with Earley algorithm
 * @return bool value which means that word belongs to grammar or not
 */
bool Earley::EarleyParse(std::string word) {
    grammar_.ClearGrammar(word);

    grammar_.AddSituations(0, Situation{'0', "",
                                        "S", 0});

    int32_t D_0_size = 0;
    do {
        D_0_size = static_cast<int32_t>(grammar_.GetSituations()[0].size());
        Complete(0);
        Predict(0);
    } while (D_0_size != static_cast<int32_t>(grammar_.GetSituations()[0].size()));

    for (int32_t j = 0; j <= word.length(); ++j) {
        Scan(j, word);

        int32_t D_j_size = 0;
        do {
            D_j_size = static_cast<int32_t>(grammar_.GetSituations()[j].size());
            Complete(j);
            Predict(j);
        } while (D_j_size != static_cast<int32_t>(grammar_.GetSituations()[j].size()));
    }

    for (auto& situation: grammar_.GetSituations()[static_cast<int32_t>(word.length())]) {
        if ((Situation) situation == Situation{'0', "S", "", 0}) {
            return true;
        }
    }

    return false;
}