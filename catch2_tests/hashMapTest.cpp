#include "catch.hpp"
#include "../HashMapWrapper.h"

using namespace std;

TEST_CASE("various dummy tests", "[hashmap]") {

    HashMapWrapper<int> hashMapWrapper;

    SECTION("Empty hashMap") {
        REQUIRE(hashMapWrapper.size() == 0);
    }

    SECTION("insert and contains") {
        for (int i : {2, 4, 6, 8, 10}) {
            hashMapWrapper.insert(i);
        }

        for (int i : {2, 4, 6, 8, 10}) {
            REQUIRE(hashMapWrapper.contains(i));
        }

        REQUIRE(hashMapWrapper.size() == 5);
        REQUIRE(!hashMapWrapper.contains(1));
    }
}
