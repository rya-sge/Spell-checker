#include "catch.hpp"
#include "../HashMapWrapper.h"
#include "../HashMapLinearProbing.h"

using namespace std;
/*
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
*/

TEST_CASE("Linear Probing", "[hashmap]") {
    HashMapLinearProbing<string> hmString;
    HashMapLinearProbing<size_t> hmSizeT;
/*
    SECTION("String values") {


        SECTION("Insert key") {
            hmString.insert("Salut");
            hmString.insert("Les amis");
            hmString.insert("Oui");

            REQUIRE(hmString.contains("Salut"));
            REQUIRE(hmString.contains("Les amis"));
            REQUIRE(hmString.contains("Oui"));
            REQUIRE(hmString.size() == 3);
        }

        SECTION("Remove key") {
            REQUIRE(hmString.contains("Salut"));

        }

        SECTION("Search key") {

        }

        SECTION("Resize hashmap") {
            SECTION("Extend") {

            }

            SECTION("Reduce") {

            }
        }
    }
*/
    SECTION("Size_T values") {
        vector<size_t> values(5);
        for(size_t &value : values)
            value = rand();

        SECTION("Insert key") {
            for(size_t val : values){
                hmSizeT.insert(val);
                REQUIRE(hmSizeT.contains(val));
            }

            REQUIRE(hmSizeT.size() == values.size());
        }

        SECTION("Remove key") {
            for(size_t val : values){
                hmSizeT.insert(val);
            }

            for(size_t val : values){
                hmSizeT.erase(val);
                REQUIRE(!hmSizeT.contains(val));
            }

            REQUIRE(!hmSizeT.size());
        }

        SECTION("Search key") {

        }

        SECTION("Resize hashmap") {
            SECTION("Extend") {

            }

            SECTION("Reduce") {

            }
        }
    }
}
