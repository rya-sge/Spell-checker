//
// Created by david on 23.01.21.
// Tests inspirés de hashMapTest.cpp
//

#include <iostream>
# include "catch.hpp"
#include "../TernarySearchTree.h"
using namespace std;


TEST_CASE("Ternary Search Tree") {
    std::string fruits[] = {"pomme", "poire", "fraise", "pasteque", "orange", "mandarine", "citron", "noix", "noisette",
                            "melon"};
    const size_t SIZE_FRUITS = 10;
    std::string suppressFruits[] = {"poire", "pasteque", "mandarine", "noix", "melon"};
    const size_t SIZE_SUPRESSED_FRUITS = 5;
    std::string BALANCE_TEST_VALUES[] = {"A", "B", "CD", "EF", "GH"};
    const size_t SIZE_BALANCE_VALUES = 5;
    TST test, balanceTest;

    SECTION("Empty Tree") {
        REQUIRE(!test.size());
    }

    SECTION("Insert key (and contains)") {
        for (string val : fruits) {
            test.insert(val, 1);
            REQUIRE(test.contains(val));
        }
        REQUIRE(test.size() == SIZE_FRUITS);
    }

    SECTION("Erase key") {
        for (string val : fruits) {
            test.insert(val, 1);
        }
        for (string val : fruits) {
            test.erase(val);
            REQUIRE(!test.contains(val));
        }
        REQUIRE(!test.size());
    }

    SECTION("Balance") {
        /* A trouver comment faire */
        for (string val :  BALANCE_TEST_VALUES) {
            balanceTest.insert(val, 1);
            REQUIRE(balanceTest.contains(val));
            REQUIRE(balanceTest.isBalanced());
        }
        REQUIRE(balanceTest.size() == SIZE_BALANCE_VALUES);
        for (string val :BALANCE_TEST_VALUES) {
            balanceTest.erase(val);
            REQUIRE(!test.contains(val));
            REQUIRE(balanceTest.isBalanced());
        }

    }

    SECTION("Insert all fruits, count and check if it is contained") {
        for (size_t i = 0; i < SIZE_FRUITS; ++i) {
            test.insert(fruits[i], i);
            REQUIRE(test.size() == i + 1);
            //Check que les éléments ne s'insérent pas à double
            test.insert(fruits[i], i);
            REQUIRE(test.size() == i + 1);
            REQUIRE(test.contains(fruits[i]));
        }
        REQUIRE(!test.contains("piment"));
    }


    SECTION("Insert all fruits, erase some, count and check if it is contained") {

        for (string fruit : fruits)
            test.insert(fruit, 1);

        for (size_t i = 0; i < SIZE_SUPRESSED_FRUITS; ++i) {
            test.erase(suppressFruits[i]);
            REQUIRE(test.size() == SIZE_FRUITS - 1 - i);
            //Check que les éléments ne s'effacent pas deux fois
            test.erase(suppressFruits[i]);
            REQUIRE(test.size() == SIZE_FRUITS - 1 - i);
        }
        for (size_t i = 0; i < SIZE_FRUITS; ++i) {
            if (i % 2)
                REQUIRE(!test.contains(fruits[i]));
            else
                REQUIRE(test.contains(fruits[i]));
        }
    }
}