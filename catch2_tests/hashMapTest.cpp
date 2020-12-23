#include <iostream>
#include <iomanip>
#include "catch.hpp"
#include "../HashMapWrapper.h"
#include "../HashMapLinearProbing.h"

using namespace std;

template <typename T>
bool test(const vector<T>& values, const vector<T>& noValues){
    HashMapLinearProbing<T> hm;

    const double MAX_FACTOR = 0.5;
    const double MIN_FACTOR = 1.0/8;

    SECTION("Empty hashMap") {
        //Vérifier que la taille est nulle
        REQUIRE(!hm.size());
        for(T val : noValues){
            REQUIRE(!hm.contains(val));
            REQUIRE(!hm.erase(val));
        }
    }

    SECTION("Insert key (and contains)") {
        for(T val : values){
            hm.insert(val);
            REQUIRE(hm.contains(val));
        }

        REQUIRE(hm.size() == values.size());
    }

    SECTION("Remove key") {
        for(T val : values){
            hm.insert(val);
        }

        for(T val : values){
            hm.erase(val);
            REQUIRE(!hm.contains(val));
        }

        REQUIRE(!hm.size());
    }

    SECTION("Resize hashmap") {
        SECTION("Extend") {
            size_t M = hm.max_size();

            for(size_t N = 0; N < values.size(); ++N){
                double factor = (double)(N+1)/M;

                hm.insert(values.at(N));

                //std::cout << setw(2)<< N+1 << "|" << M << "|" <<  factor << endl;

                if(factor >= MAX_FACTOR){ // realloc expected
                    double actualFactor = (double)hm.size() / hm.max_size();

                    //std::cout << "\t" << hm.size() << " / " << hm.max_size() << " = " << actualFactor << endl;
                    REQUIRE(actualFactor == factor/2);
                    M = hm.max_size();
                }

            }

        }

        SECTION("Reduce") {
            for(T val: values)
                hm.insert(val);

            size_t M = hm.max_size();
            for(int N = hm.size() - 1; N >= 0; --N){
                double factor = (double)N/M;
                hm.erase(values.at(N));

                //std::cout << setw(2)<< N << "|" << M << "|" <<  factor << endl;
                if(factor <= MIN_FACTOR){ // realloc expected
                    double actualFactor = (double)hm.size() / hm.max_size();

                    //std::cout << "\t" << hm.size() << " / " << hm.max_size() << " = " << actualFactor << endl;
                    REQUIRE((actualFactor == factor*2));
                    M = hm.max_size();
                }

            }

        }
    }

}



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


TEST_CASE("Linear Probing", "[hashmap]") {
    HashMapLinearProbing<string> hmString;
    HashMapLinearProbing<size_t> hmSizeT;

    SECTION("Size_T values") {
        const size_t SIZE = 5;
        vector<size_t> values(SIZE);
        vector<size_t> valuesExclude(SIZE);
        for(int i = 0; i < values.size(); ++i ){
            values.at(i) = i;
        }
        for(int elem = values.size(), i = 0; i < valuesExclude.size(); ++i, ++elem ){
            valuesExclude.at(i) = elem;
        }
        test(values, valuesExclude);

    }

    SECTION("String values") {
        vector<string> values = {"H", "Salut", "Les amis", "Oui"};
        vector<string> valuesExclude = {"h", "tulaS", "Non", "Enjoy"};
        test(values, valuesExclude);
    }
}
