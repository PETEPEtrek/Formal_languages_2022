//
// Created by Acer on 05.10.2022.
//

#include "gtest/gtest.h"
#include "ksuffix.hpp"

TEST(KSuffix, checkSymbols) {
    std::string backP = "ab.";
    char letter = 'b';
    int64_t k = 2;
    KSuffix k_suffix{backP, letter, k};
    ASSERT_EQ(k_suffix.isCorrectSymbol('k'), false);
    ASSERT_EQ(k_suffix.isCorrectSymbol('a'), true);
    ASSERT_EQ(k_suffix.isCorrectSymbol('1'), true);
    ASSERT_EQ(k_suffix.isCorrectSymbol('*'), true);
    ASSERT_EQ(k_suffix.isCorrectSymbol('+'), true);
    ASSERT_EQ(k_suffix.isCorrectSymbol('.'), true);
}


TEST(KSuffix, checkKleeneStarCase) {
    using Lengths = std::unordered_set<int64_t>;
    using States = std::unordered_map<int64_t, Lengths>;
    std::string backP = "aa.*";
    char letter = 'a';
    int64_t k = 5;
    KSuffix k_suffix{backP, letter, k};
    std::stack<States> test_stack_{};
    test_stack_.push({{2, {2}}});

    std::stack<States> answer{};
    answer.push({{0, {0}}, {2, {2}}, {4, {4}}});
    k_suffix.KleeneStarCase(test_stack_);
    ASSERT_EQ(test_stack_, answer);
}


TEST(KSuffix, checkPlus) {
    using Lengths = std::unordered_set<int64_t>;
    using States = std::unordered_map<int64_t, Lengths>;
    std::string backP = "ab+";
    char letter = 'a';
    int64_t k = 1;
    KSuffix k_suffix{backP, letter, k};
    std::stack<States> test_stack_{};
    test_stack_.push({{1, {1}}});
    test_stack_.push({{0, {1}}});

    std::stack<States> answer{};
    answer.push({{0, {1}}, {1, {1}}});
    k_suffix.PlusCase(test_stack_);
    ASSERT_EQ(test_stack_, answer);
}


TEST(KSuffix, checkConcat) {
    using Lengths = std::unordered_set<int64_t>;
    using States = std::unordered_map<int64_t, Lengths>;
    std::string backP = "ab.c.";
    char letter = 'c';
    int64_t k = 1;
    KSuffix k_suffix{backP, letter, k};
    std::stack<States> test_stack_{};
    test_stack_.push({{0, {1}}});
    test_stack_.push({{0, {1}}});

    std::stack<States> answer{};
    answer.push({{0, {2}}});
    k_suffix.ConcatCase(test_stack_);
    ASSERT_EQ(test_stack_, answer);

    test_stack_.push({{1, {1}}});
    answer.pop();
    answer.push({{1, {3}}});
    k_suffix.ConcatCase(test_stack_);
    ASSERT_EQ(test_stack_, answer);
}

TEST(KSuffix, EasyCases) {
    std::string backP = "ab.c.";
    char letter = 'c';
    int64_t k = 1;
    KSuffix k_suffix{backP, letter, k};
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "3");

    k_suffix.ChangeK(2);
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "INF");


    k_suffix.ChangeNotation("ab.1+");
    k_suffix.ChangeX('b');
    k_suffix.ChangeK(1);
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "2");


    k_suffix.ChangeNotation("aa.*");
    k_suffix.ChangeX('a');
    k_suffix.ChangeK(3);
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "INF");

}

TEST(KSuffix, HarderCases) {
    std::string backP = "ab+c.aba.*.bac.+.+*";
    char letter = 'b';
    int64_t k = 2;
    KSuffix k_suffix{backP, letter, k};

    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "INF");

    k_suffix.ChangeNotation("acb..bab.c.*.ab.ba.+.+*a.");
    k_suffix.ChangeX('a');
    k_suffix.ChangeK(2);
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "4");


    k_suffix.ChangeNotation("ab+*b.1+b.ab+*.");
    k_suffix.ChangeX('a');
    k_suffix.ChangeK(3);
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "4");
}


TEST(KSuffix, BadCases) {
    std::string backP = "There are incorrect symbols in this notation";
    char letter = 'a';
    int64_t k = 2;
    KSuffix k_suffix{backP, letter, k};
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "Bad Notation: bad symbols!");

    k_suffix.ChangeNotation("aa");
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "Bad Notation: stack is not empty!");

    k_suffix.ChangeNotation("*");
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "Bad Notation: not enough operands in notation for *");

    k_suffix.ChangeNotation("+");
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "Bad Notation: not enough operands in notation for +");

    k_suffix.ChangeNotation(".");
    ASSERT_EQ(k_suffix.FindLenOfKSuffix(), "Bad Notation: not enough operands in notation for .");
}

TEST(KSuffix, EquivalentAutomats) {
    std::string backPFirst = "aa.b+ab.+*";
    std::string backPSecond = "ab+*b.1+aa.*.";

    char letter = 'a';
    int64_t k = 4;

    KSuffix k_suffix_first{backPFirst, letter, k};
    KSuffix k_suffix_second{backPSecond, letter, k};

    ASSERT_EQ(k_suffix_first.FindLenOfKSuffix(), k_suffix_second.FindLenOfKSuffix());
    ASSERT_EQ(k_suffix_first.FindLenOfKSuffix(), "4");

    k_suffix_first.ChangeK(5);
    ASSERT_EQ(k_suffix_first.FindLenOfKSuffix(), "INF");
}