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

/**
 * Les différents tests du Ternary Search Tree comportent des vérifications sur
 *  contains
 *  insert
 *  size
 *  erase
 * De plus des tests sont faits sur l'équilibrage de l'arbre et des sous arbres
 */
TEST_CASE("Ternary Search Tree") {

    vector<string> fruits = {"pomme", "poire", "fraise", "pasteque", "orange", "mandarine", "citron", "noix",
                             "noisette",
                             "melon"};
    vector<string> suppressFruits = {"poire", "pasteque", "mandarine", "noix", "melon"};

    vector<string> BALANCE_TEST_VALUES = {"A", "B", "CD", "EF", "GH"};
    TST test, balanceTest;

    /**
     * Vérification que l'arbre vide a une taille de 0
     */
    SECTION("Arbre vide") {
        REQUIRE(!test.size());
    }

        /**
         * Vérification qu'une clé insérée soit contenue
         */
    SECTION("Insertion et vérification du contenu") {
        for (string const &val : fruits) {
            test.insert(val, 1);
            REQUIRE(test.contains(val));
        }
        REQUIRE(test.size() == fruits.size());
    }

        /**
         * Insertion d'éléments.
         * Supression de ceux-ci.
         * Vérification que ceux-ci ne soit plus contenus
         * après chaque supressions.
         */
    SECTION("Suppression") {
        for (const string &val : fruits) {
            test.insert(val, 1);
        }
        for (size_t i = 0; i < fruits.size(); ++i) {
            test.erase(fruits.at(i));
            REQUIRE(!test.contains(fruits.at(i)));
            if (i < fruits.size() - 1) {
                REQUIRE(test.contains(fruits.at(i + 1)));
            }
            REQUIRE(balanceTest.isBalanced());
        }
        REQUIRE(!test.size());
    }

        /**
         * Test qu'après chaque insertion et suppression
         * d'éléments, contains soit correcte et que
         * tous les arbres et sous arbres soient équilibrés,
         */
    SECTION("Equilibrage") {
        for (const string &val :  BALANCE_TEST_VALUES) {
            balanceTest.insert(val, 1);
            REQUIRE(balanceTest.contains(val));
            REQUIRE(balanceTest.isBalanced());
        }
        REQUIRE(balanceTest.size() == BALANCE_TEST_VALUES.size());
        for (const string &val :BALANCE_TEST_VALUES) {
            balanceTest.erase(val);
            REQUIRE(!test.contains(val));
            REQUIRE(balanceTest.isBalanced());
        }

    }

        /*
         * Tests de toutes les fonctionalités du TST sauf erase
         */
    SECTION("Insertion des fruits, vérifie la taille, le contenu et l'équilibrage") {
        for (size_t i = 0; i < fruits.size(); ++i) {
            test.insert(fruits[i], i);
            REQUIRE(test.size() == i + 1);
            //Check que les éléments ne s'insérent pas à double
            test.insert(fruits[i], i);
            REQUIRE(test.size() == i + 1);
            REQUIRE(test.contains(fruits[i]));
            REQUIRE(test.isBalanced());
        }
        REQUIRE(!test.contains("piment"));
    }

        /*
         * Tests de toutes les fonctionalités du TST avec erase
         */
    SECTION("Insertion des fruits, suppression de certains, vérifie la taille, le contenu et l'équilibrage") {

        for (const string &fruit : fruits)
            test.insert(fruit, 1);

        for (size_t i = 0; i < suppressFruits.size(); ++i) {
            test.erase(suppressFruits[i]);
            REQUIRE(test.size() == fruits.size() - 1 - i);
            //Vérifie que les éléments ne s'effacent pas deux fois
            test.erase(suppressFruits[i]);
            REQUIRE(test.size() == fruits.size() - 1 - i);
            REQUIRE(test.isBalanced());
        }
        for (size_t i = 0; i < fruits.size(); ++i) {
            if (i % 2)
                REQUIRE(!test.contains(fruits[i]));
            else
                REQUIRE(test.contains(fruits[i]));
        }
    }
}