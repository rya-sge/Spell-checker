/* ---------------------------
Laboratoire : 8 - Correcteur orthographique
Fichier : TST_Test.cpp
Auteurs : David Pellissier, Michael Ruckstuhl, Ryan Sauge
Date : 23.01.2021

But : Tests de la structure Ternary Search Tree. Inspirés des tests de HashMap.

Compilateur : gcc 9.3.0
--------------------------- */


# include "catch.hpp"
# include "../TernarySearchTree.h"
using namespace std;


TEST_CASE("Ternary Search Tree") {

    vector<string> fruits = {"pomme", "poire", "fraise", "pasteque", "orange", "mandarine", "citron", "noix", "noisette",
                            "melon"};
    vector<string> suppressFruits = {"poire", "pasteque", "mandarine", "noix", "melon"};

    vector<string> BALANCE_TEST_VALUES = {"A", "B", "CD", "EF", "GH"};
    TST test, balanceTest;

    SECTION("Empty Tree") {
        REQUIRE(!test.size());
    }

    SECTION("Insert key (and contains)") {
        for (string val : fruits) {
            test.insert(val, 1);
            REQUIRE(test.contains(val));
        }
        REQUIRE(test.size() == fruits.size());
    }

    SECTION("Erase key") {
        for (string val : fruits) {
            test.insert(val, 1);
        }
        for(size_t i = 0; i < fruits.size(); ++i){
            test.erase(fruits.at(i));
            REQUIRE(!test.contains(fruits.at(i)));
            if(i <  fruits.size() - 1 ){
                REQUIRE(test.contains(fruits.at(i + 1)));
            }
            REQUIRE(balanceTest.isBalanced());
        }
        REQUIRE(!test.size());
    }

    SECTION("Balance") {
        for (string val :  BALANCE_TEST_VALUES) {
            balanceTest.insert(val, 1);
            REQUIRE(balanceTest.contains(val));
            REQUIRE(balanceTest.isBalanced());
        }
        REQUIRE(balanceTest.size() == BALANCE_TEST_VALUES.size());
        for (string val :BALANCE_TEST_VALUES) {
            balanceTest.erase(val);
            REQUIRE(!test.contains(val));
            REQUIRE(balanceTest.isBalanced());
        }

    }

    SECTION("Insert all fruits, count and check if it is contained") {
        for (size_t i = 0; i < fruits.size(); ++i) {
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

        for (size_t i = 0; i < suppressFruits.size(); ++i) {
            test.erase(suppressFruits[i]);
            REQUIRE(test.size() == fruits.size() - 1 - i);
            //Check que les éléments ne s'effacent pas deux fois
            test.erase(suppressFruits[i]);
            REQUIRE(test.size() == fruits.size() - 1 - i);
        }
        for (size_t i = 0; i <fruits.size(); ++i) {
            if (i % 2)
                REQUIRE(!test.contains(fruits[i]));
            else
                REQUIRE(test.contains(fruits[i]));
        }
    }
}