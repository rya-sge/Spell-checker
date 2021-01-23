/* ---------------------------
Laboratoire : 8 - Correcteur orthographique
Fichier : hashMapTest.cpp
Auteurs : David Pellissier, Michael Ruckstuhl, Ryan Sauge
Date : 23.01.2021

But : Test des différentes hashmaps

Compilateur : gcc 9.3.0
--------------------------- */

#include <iostream>
#include "catch.hpp"
#include "../HashMap/HashMapWrapper.h"
#include "../HashMap/HashMapLinearProbing.h"
#include "../HashMap/HashMapSeparateChaining.h"

using namespace std;

const size_t SIZE_VECTOR_TEST = 20;
const size_t N = 100;

const vector<string> FRUITS = {"pomme", "poire", "fraise", "pasteque", "orange", "mandarine", "citron", "noix", "noisette",
                         "melon"};
const vector<string> FRUITS_A_SUPPRIMER = {"poire", "pasteque", "mandarine", "noix", "melon"};

const vector<string> FRUITS_EXCLUS = {"h", "tulaS", "Non", "Enjoy"};


#include <memory> // for std::allocator


/**
 *
 * @tparam T
 * @param hm
 * @param keys
 * @param noKeys contient une liste de clés qui ne doient pas être présent dans keys
 * @details test Empty hashMap, insert and contains, erase, resize, reduce with specified vectors
 *
 */
template<typename T>
void testCommonGeneral(HashMapWrapper<T> *hm, vector<T> keys, std::vector<T> noKeys, std::vector<T> keyToDelete) {
    SECTION("HashMap vide") {
        REQUIRE(!hm->size());

    }

    SECTION("Contain et Erase sur des clés non contenues dans la hashmap") {
        for (T val : noKeys) {
            REQUIRE(!hm->contains(val));
            REQUIRE(!hm->erase(val));
        }
    }


    SECTION("Insert key (et contains)") {
        for (T val : keys) {
            hm->insert(val);
            REQUIRE(hm->contains(val));
        }

        REQUIRE(hm->size() == keys.size());
    }

    SECTION("Erase key") {
        for (T val : keys) {
            hm->insert(val);
        }

        for (T val : keys) {
            hm->erase(val);
            REQUIRE(!hm->contains(val));
        }

        REQUIRE(!hm->size());
    }

    SECTION("Insère des éléments de keys, supprime les cls specifies par noKeys count and check if it is contained") {

        for (size_t i = 0; i < keys.size(); ++i){
            hm->insert(keys[i]);
            REQUIRE(hm->contains(keys[i]));
        }


        for (size_t i = 0; i < keyToDelete.size(); ++i) {
            hm->erase(keyToDelete[i]);
            REQUIRE(hm->size() == keys.size() - 1 - i);
            //Check que les éléments ne s'effacent pas deux fois
            hm->erase(keyToDelete[i]);
            REQUIRE(!hm->contains(keyToDelete[i]));
            REQUIRE(hm->size() == keys.size() - 1 - i);
        }
    }

    SECTION("Resize hashmap") {
        SECTION("Extend") {
            size_t M = hm->max_buckets();

            for (size_t N = 0; N < keys.size(); ++N) {
                double factor = (double) (N + 1) / M;

                hm->insert(keys.at(N));

                if (factor >= hm->getMaxFactor()) { // realloc expected
                    double actualFactor = (double) hm->size() / hm->max_buckets();
                    REQUIRE(actualFactor == (factor / hm->getMulCoefFactor()));
                    M = hm->max_buckets();
                }

            }

        }

        SECTION("Reduce") {
            for (T val: keys)
                hm->insert(val);

            size_t M = hm->max_buckets();
            for (int n = hm->size() - 1; n >= 0; --n) {
                hm->erase(keys.at(n));
                double factor = (double) n / M;
                double actualFactor = (double) hm->size() / hm->max_buckets();
                if (M == hm->getMinValueForM()) {
                    REQUIRE((actualFactor == factor));
                } else if (factor <= hm->getMinFactor()) { // realloc expected
                    REQUIRE((actualFactor == (factor * hm->getDivCoefFactor())));
                    M = hm->max_buckets();
                }

            }

        }
    }
}

/**
 * @tparam T seulement des types numériques(int, double, char) -> String pas possible
 * @param hm
 * @param n nombre d'éléments utilisés pour le test de la hashmap
 * @details
 * - test size(), insert() et contains(), erase() avec une taille spécifique
 * - Permet de réaliser des tests avec beaucoups d'éléments.
 */
template<typename T>
void testCommonSize(HashMapWrapper<T> *hm, T n) {
    SECTION("New size, is 0") {
        REQUIRE(hm->size() == 0);
    }SECTION("size == i, i in [1,...,n], with insert") {
        for (T i = 1; i <= n; ++i) {
            hm->insert(i);
            REQUIRE(hm->size() == i);
            //Check que les éléments ne s'insérent pas à double
            hm->insert(i);
            REQUIRE(hm->size() == i);
        }
    }SECTION("contains == i, i in [1,...,n], avec insert où les éléments 2k, k in R") {

        for (T i = 1; i <= n; ++i) {
            if (i % 2)
                hm->insert(i);
        }

        for (T i = 1; i <= n; ++i) {
            if (i % 2)
                REQUIRE(hm->contains(i));
            else
                REQUIRE(!hm->contains(i));
        }
    }SECTION("size == i, i in [1,...,n], with erase") {
        for (T i = 1; i <= n; ++i) {
            hm->insert(i);
        }
        for (T i = 1; i <= n; ++i) {
            hm->erase(i);
            REQUIRE(hm->size() == n - i);
            //check qu'il n'ait aucune modification quand on supprime un élément déjà supprimé.
            hm->erase(i);
            REQUIRE(hm->size() == n - i);
        }
    }SECTION("contains == i, i in [1,...,n], with erase for elements that are 2k, k in R") {
        for (T i = 1; i <= n; ++i) {
            hm->insert(i);
            if (i % 2)
                hm->erase(i);
        }
        for (T i = 1; i <= n; ++i) {
            if (i % 2)
                REQUIRE(!hm->contains(i));
            else
                REQUIRE(hm->contains(i));
        }
    }

}

/**
 * @brief Préparation d'un vecteur de test
 * @param values
 * @param valuesExclude
 */
template <typename T>
void prepareVector(vector<T> &values, vector<T> &valuesExclude, vector<T> &valuesErase) {
    for (T i = 0; i < values.size(); ++i) {
        values.at(i) = i;
    }
    for (T elem = values.size(), i = 0; i < valuesExclude.size(); ++i, ++elem) {
        valuesExclude.at(i) = elem;
    }

    for (T i = 0; i < valuesErase.size(); ++i) {
        valuesErase.at(i) = i;
    }
}

template<typename T>
void testCommonFunction(HashMapWrapper<T>& hm,  HashMapWrapper<T>& hm2, HashMapWrapper<string>& strings){
    SECTION("Valeurs numériques de type T") {
        vector<T> values(SIZE_VECTOR_TEST);
        vector<T> valuesExclude(SIZE_VECTOR_TEST);
        vector<T> valuesDelete(SIZE_VECTOR_TEST / 3);
        prepareVector(values, valuesExclude,  valuesDelete);

        auto *hw = reinterpret_cast<HashMapWrapper<T> *>(&hm);
        testCommonGeneral(hw, values, valuesExclude, valuesDelete);

        auto *hw2 = reinterpret_cast<HashMapWrapper<T> *>(&hm2);
        testCommonSize(hw2, N);
    }

    SECTION("Test avec des strings") {
        vector<string> values(FRUITS);
        auto *hw = reinterpret_cast<HashMapWrapper<std::string> *>(&strings);
        testCommonGeneral(hw, values, FRUITS_EXCLUS, FRUITS_A_SUPPRIMER);
    }

}


/**
 * Test de Linear Probing
 */
TEST_CASE("Linear Probing", "[hashmap]") {
    HashMapLinearProbing<size_t> lb;
    HashMapLinearProbing<size_t> lb2;
    HashMapLinearProbing<string> strings;
    testCommonFunction(lb, lb2, strings);
}

/**
 * Test de Separate Chaining
 */
TEST_CASE("SeparateChaining", "[hashmap]") {
    HashMapSeparateChaining<size_t> sc;
    HashMapSeparateChaining<size_t> sc2;
    HashMapSeparateChaining<string> strings;
    auto *hw = reinterpret_cast<HashMapWrapper<std::string> *>(&strings);
    testCommonFunction(sc, sc2, strings);
}

