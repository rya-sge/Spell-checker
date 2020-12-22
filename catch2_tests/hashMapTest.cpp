#include <iostream>
#include <iomanip>
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

    const double MAX_FACTOR = 0.5;
    const double MIN_FACTOR = 1.0/8;

    SECTION("Size_T values") {
        vector<size_t> values(10);
        for(size_t &value : values)
            value = rand();

        SECTION("Insert key (and contains)") {
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

        SECTION("Resize hashmap") {
            SECTION("Extend") {


            }

            SECTION("Reduce") {
                for(size_t val: values)
                    hmSizeT.insert(val);

                size_t M = hmSizeT.max_size();
                for(size_t N = hmSizeT.size()-1; N >= 0; --N){
                    double factor = (double)(N)/M;
                    hmSizeT.erase(values.at(N));
                    //std::cout << setw(2)<< N << "|" << M << "|" <<  factor << endl;
                    if(factor <= MIN_FACTOR){ // realloc expected
                        double actualFactor = (double)hmSizeT.size()/hmSizeT.max_size();
                        //std::cout << "\t" << hmSizeT.size() << " / " << hmSizeT.max_size() << " = " << actualFactor << endl;
                        REQUIRE(actualFactor == factor*2);
                        M = hmSizeT.max_size();
                    }

                }

            }
        }
    }
}
