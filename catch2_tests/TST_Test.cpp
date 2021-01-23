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

    TST test;

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
            cout << val << ": " << test.contains(val) << endl;
            REQUIRE(!test.contains(val));
        }
        REQUIRE(!test.size());
    }

    SECTION("Balance") {
        /* A trouver comment faire */
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

/*
TST test;
test.insert("Pomme",1);
test.insert("Poir", 2);
test.insert("Melon", 3);

cout << "size of tst is: " << test.size() << endl;

cout << "Pomme: " << test.contains("Pomme") << endl;
cout << "Poir: " << test.contains("Poir") << endl;
cout << "Melon: " << test.contains("Melon") << endl;

cout << "Orange: " << test.contains("Orange") << endl;
cout << "Fraise: " << test.contains("Fraise") << endl;
cout << "Noix: " << test.contains("Noix") << endl;

test.erase("Pomme");
test.erase("Pomme");
test.erase("Poir");
test.erase("Noix");

cout << "size of tst is: " << test.size() << endl;

cout << "Pomme: " << test.contains("Pomme") << endl;
cout << "Poir: " << test.contains("Poir") << endl;
cout << "Melon: " << test.contains("Melon") << endl;

cout << "Orange: " << test.contains("Orange") << endl;
cout << "Fraise: " << test.contains("Fraise") << endl;
cout << "Noix: " << test.contains("Noix") << endl;


return 0;*/