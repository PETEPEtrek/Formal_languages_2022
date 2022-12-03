//
// Created by Acer on 03.12.2022.
//

#include "gtest/gtest.h"
#include "../src/Grammar.hpp"

TEST(Grammar, checkRules) {
    Grammar example;
    std::string first = "asdas";
    std::string second = "vsdgs";
    std::string third = "gasdg";
    std::string fourth = "asdgsg";
    example.AddRule('A', first);
    example.AddRule('B', second);
    example.AddRule('C', third);
    example.AddRule('D', fourth);

    std::vector<std::pair<char, std::string>> rules = {{'A', first}, {'B', second},
                                                       {'C', third}, {'D', fourth}};

    ASSERT_EQ(example.GetRules(), rules);
}