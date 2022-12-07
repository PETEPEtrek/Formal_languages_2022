#include "src/Earley.hpp"
#include <iostream>

int main() {
    std::string breakpoint;

    std::cout << "Hello! This app takes a grammar rules, builds a grammar and after that"
                 " takes words and decides whether it belongs to grammar or not using Earley algorithm" << "\n";

    while (true) {
        std::cout << "Please type the grammar rules; if you want to stop, type 'Stop': ";
        bool start_nonterminal = false;
        Grammar grammar;
        std::string stop;
        while (true) {
            char Start;
            std::string right_part;
            while (true) {
                std::cin >> Start >> right_part;
                if (Start == 'S') {
                    start_nonterminal = true;
                }
                if (Start < 'A' || Start > 'Z') {
                    std::cout
                        << "Please write again, it seems that in left part of rule is terminal element, you can only use A-Z";
                } else {
                    break;
                }
            }
            if (right_part == "#") {
                right_part = "";
            }
            grammar.AddRule(Start, right_part);
            std::cout << "Stop?" << "\n";
            std::cin >> stop;
            if (stop == "Stop" && start_nonterminal) {
                break;
            } else if (!start_nonterminal) {
                std::cout << "Please, add at least one start rule" << "\n";
            }
        }
        Earley earley(grammar);
        std::cout << "Now you can check your words for belonging to your grammar :" << "\n";
        while (true) {
            std::string word;
            std::cin >> word;
            if (earley.EarleyParse(word) == 1) {
                std::cout << "This word belongs to grammar" << "\n";
            } else {
                std::cout << "This word doesn't belong to grammar" << "\n";
            }
            std::cout << "Type 'Stop' if you want to stop : ";
            std::cin >> word;
            if (word == "Stop") {
                break;
            }
            std::cout << "Type a new word: ";
        }
        std::cout << "Do you want to create another grammar? Type 'No' if you don't want to: ";
        std::cin >> breakpoint;
        if (breakpoint == "No") {
            break;
        }
    }
    return 0;
}