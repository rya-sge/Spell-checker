#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "catch.hpp"
#include "../HashMapSeparateChaining.h"

/*
 * Make Separate Chaining great again
 */

/*
 * insert
 */

const size_t N = 100;


TEST_CASE("Separate Chaining with size_t") {

    HashMapSeparateChaining<size_t> sp;

    SECTION("New size, is 0") {
        REQUIRE(sp.size() == 0);
    }SECTION("size == i, i in [1,...,N], with insert") {
        for (size_t i = 1; i <= N; ++i) {
            sp.insert(i);
            REQUIRE(sp.size() == i);
            //Check que les éléments ne s'insérent pas à double
            sp.insert(i);
            REQUIRE(sp.size() == i);
        }
    }SECTION("contains == i, i in [1,...,N], with insert where elements are 2k, k in R") {

        for (size_t i = 1; i <= N; ++i) {
            if(i%2)
                sp.insert(i);
        }

        for (size_t i = 1; i <= N; ++i) {
            if(i%2)
                REQUIRE(sp.contains(i));
            else
                REQUIRE(!sp.contains(i));
        }
    }SECTION("size == i, i in [1,...,N], with erase") {
        for (size_t i = 1; i <= N; ++i) {
            sp.insert(i);
        }
        for (size_t i = 1; i <= N; ++i) {
            sp.erase(i);
            REQUIRE(sp.size() == N - i);
            //check que l'élément ne déjà effecé ne modifie rien
            sp.erase(i);
            REQUIRE(sp.size() == N - i);
        }
    }
    SECTION("contains == i, i in [1,...,N], with erase for elements that are 2k, k in R") {
        for (size_t i = 1; i <= N; ++i) {
            sp.insert(i);
            if(i%2)
                sp.erase(i);
        }
        for (size_t i = 1; i <= N; ++i) {
            if(i%2)
                REQUIRE(!sp.contains(i));
            else
                REQUIRE(sp.contains(i));
        }
    }
}


TEST_CASE("Separate Chaining with string") {

    HashMapSeparateChaining<std::string> sp;
    std::string fruits[] = {"pomme","poire","fraise","pasteque","orange","mandarine","citron","noix", "noisette", "melon"};
    std::string suppressFruits[] = {"poire","pasteque","mandarine","noix", "melon"};

    SECTION("New size, is 0") {
        REQUIRE(sp.size() == 0);
    }SECTION("insert all fruits, count and check if it is contained") {
        for (size_t i = 0; i < fruits->length(); ++i) {
            sp.insert(fruits[i]);
            REQUIRE(sp.size() == i + 1);
            //Check que les éléments ne s'insérent pas à double
            sp.insert(fruits[i]);
            REQUIRE(sp.size() == i + 1);
            REQUIRE(sp.contains(fruits[i]));
        }
        REQUIRE(!sp.contains("piment"));
    }SECTION("insert all fruits, erase some, count and check if it is contained") {

        for (size_t i = 0; i < fruits->length(); ++i)
            sp.insert(fruits[i]);

        for (size_t i = 0; i < suppressFruits->length(); ++i) {
            sp.erase(suppressFruits[i]);
            REQUIRE(sp.size() == fruits->length() -1 - i);
            //Check que les éléments ne s'insérent pas à double
            sp.erase(suppressFruits[i]);
            REQUIRE(sp.size() == fruits->length() -1 - i);
        }
        for (size_t i = 0; i < fruits->length(); ++i){
            if(i%2)
                REQUIRE(sp.contains(fruits[i]));
            else
                REQUIRE(!sp.contains(fruits[i]));
        }
    }
}