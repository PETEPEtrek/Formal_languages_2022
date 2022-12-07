//
// Created by Acer on 03.12.2022.
//

#include "gtest/gtest.h"
#include "../src/Earley.hpp"
#include <string>
#include <set>

TEST(Earley, checkScan) {
    Grammar grammar("aba");
    grammar.AddRule('S', "ab");
    grammar.AddSituations(0, Situation{'0', "", "S", 0});
    grammar.AddSituations(0, Situation{'S', "", "ab", 0});

    Earley earley(grammar);
    earley.Scan(0, "aba");
    std::set<Situation> first_example;
    first_example.insert(Situation{'0', "", "S", 0});
    first_example.insert(Situation{'S', "", "ab", 0});
    ASSERT_EQ(earley.GetGrammar().GetSituations()[0], first_example);

    earley.Scan(1, "aba");
    std::set<Situation> second_example;
    second_example.insert(Situation{'S', "a", "b", 0});
    ASSERT_EQ(earley.GetGrammar().GetSituations()[1], second_example);
}

TEST(Earley, checkPredict) {
    Grammar grammar("aba");

    grammar.AddRule('S', "ab");
    grammar.AddRule('S', "bca");
    grammar.AddRule('S', "c");

    grammar.AddSituations(0, Situation{'0', "", "S", 0});

    Earley earley(grammar);
    earley.Predict(0);

    std::set<Situation> example;
    example.insert(Situation{'0', "", "S", 0});
    example.insert(Situation{'S', "", "ab", 0});
    example.insert(Situation{'S', "", "bca", 0});
    example.insert(Situation{'S', "", "c", 0});
    ASSERT_EQ(earley.GetGrammar().GetSituations()[0], example);
}

TEST(Earley, checkComplete) {
    std::string aba = "aba";
    Grammar grammar(aba);

    grammar.AddSituations(0, Situation{'0', "", "S", 0});
    grammar.AddSituations(2, Situation{'S', "ab", "", 0});
    grammar.AddSituations(2, Situation{'S', "ab", "c", 0});


    Earley earley(grammar);
    earley.Complete(2);

    std::set<Situation> example;
    example.insert(Situation{'0', "S", "", 0});
    example.insert(Situation{'S', "ab", "", 0});
    example.insert(Situation{'S', "ab", "c", 0});
    ASSERT_EQ(earley.GetGrammar().GetSituations()[2], example);

}

TEST(Earley, SimpleGrammar) {
    Grammar grammar;

    grammar.AddRule('S', "ab");

    Earley earley(grammar);

    ASSERT_EQ(earley.EarleyParse("ab"), 1);
    ASSERT_EQ(earley.EarleyParse("a"), 0);
    ASSERT_EQ(earley.EarleyParse("aba"), 0);
    ASSERT_EQ(earley.EarleyParse("ba"), 0);
}


TEST(Earley, Palindrome) {
    Grammar grammar;

    grammar.AddRule('S', "aSa");
    grammar.AddRule('S', "bSb");
    grammar.AddRule('S', "");
    grammar.AddRule('S', "a");
    grammar.AddRule('S', "b");

    Earley earley(grammar);

    ASSERT_EQ(earley.EarleyParse("ab"), 0);
    ASSERT_EQ(earley.EarleyParse("a"), 1);
    ASSERT_EQ(earley.EarleyParse("c"), 0);
    ASSERT_EQ(earley.EarleyParse("aba"), 1);
    ASSERT_EQ(earley.EarleyParse("ba"), 0);
    ASSERT_EQ(earley.EarleyParse("ababaabbabbabbaababa"), 1);
}

TEST(Earley, CorrectBracketSequence) {
    Grammar grammar;

    grammar.AddRule('S', "SS");
    grammar.AddRule('S', "(S)");
    grammar.AddRule('S', "()");

    Earley earley(grammar);

    ASSERT_EQ(earley.EarleyParse(")("), 0);
    ASSERT_EQ(earley.EarleyParse("()"), 1);
    ASSERT_EQ(earley.EarleyParse("("), 0);
    ASSERT_EQ(earley.EarleyParse("((()))"), 1);
    ASSERT_EQ(earley.EarleyParse("())"), 0);
    ASSERT_EQ(earley.EarleyParse("((()()(())))"), 1);
}