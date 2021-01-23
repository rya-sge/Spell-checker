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
    std::string fruits[] = {"pomme", "poire", "fraise", "pasteque", "orange", "mandarine", "citron", "noix", "noisette",
                            "melon"};
    const size_t SIZE_FRUITS = 10;
    std::string suppressFruits[] = {"poire", "pasteque", "mandarine", "noix", "melon"};
    const size_t SIZE_SUPRESSED_FRUITS = 5;
    std::string BALANCE_TEST_VALUES[] = {"A", "B", "CD", "EF", "GH"};
    const size_t SIZE_BALANCE_VALUES = 5;
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
        for (string val : fruits) {
            test.insert(val, 1);
            REQUIRE(test.contains(val));
        }
        REQUIRE(test.size() == SIZE_FRUITS);
    }

    /**
     * Insertion d'éléments.
     * Supression de ceux-ci.
     * Vérification que ceux-ci ne soit plus contenus
     * après chaque supressions.
     */
    SECTION("Suppression") {
        for (string val : fruits) {
            test.insert(val, 1);
        }
        for (string val : fruits) {
            test.erase(val);
            REQUIRE(!test.contains(val));
        }
        REQUIRE(!test.size());
    }

    /**
     * Test qu'après chaque insertion et suppression
     * d'éléments, contains soit correcte et que
     * tous les arbres et sous arbres soient équilibrés,
     */
    SECTION("Equilibrage") {
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

    /*
     * Tests de toutes les fonctionalités du TST sauf erase
     */
    SECTION("Insertion des fruits, vérifie la taille, le contenu et l'équilibrage") {
        for (size_t i = 0; i < SIZE_FRUITS; ++i) {
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
    SECTION("Insertion des fruits, suppresion de certains, vérifie la taille, le contenu et l'équilibrage") {

        for (string fruit : fruits)
            test.insert(fruit, 1);

        for (size_t i = 0; i < SIZE_SUPRESSED_FRUITS; ++i) {
            test.erase(suppressFruits[i]);
            REQUIRE(test.size() == SIZE_FRUITS - 1 - i);
            //Vérifie que les éléments ne s'effacent pas deux fois
            test.erase(suppressFruits[i]);
            REQUIRE(test.size() == SIZE_FRUITS - 1 - i);
            REQUIRE(test.isBalanced());
        }
        for (size_t i = 0; i < SIZE_FRUITS; ++i) {
            if (i % 2)
                REQUIRE(!test.contains(fruits[i]));
            else
                REQUIRE(test.contains(fruits[i]));
        }
    }
}