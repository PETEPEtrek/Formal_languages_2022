//
// Created by Acer on 03.12.2022.
//

#include "gtest/gtest.h"
#include "../src/Situation.hpp"



TEST(Situation, checkParametres) {
    Situation example{'A', "asd", "sadas", 3};
    ASSERT_EQ(example.GetA(), 'A');
    ASSERT_EQ(example.GetAlpha(), "asd");
    ASSERT_EQ(example.GetI(), 3);
}

TEST(Situation, checkOperators) {
    Situation first{'A', "asd", "sadas", 3};
    Situation second{'A', "asd", "sadas", 3};
    ASSERT_EQ(first, second);

    Situation third{'B', "asd", "sadas", 3};
    ASSERT_EQ(third > first, true);
    ASSERT_EQ(first < third, true);
    ASSERT_EQ(third >= first, true);
    ASSERT_EQ(first <= third, true);
}