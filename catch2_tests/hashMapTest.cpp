#include <iostream>
#include <iomanip>
#include "catch.hpp"
#include "../HashMap/HashMapWrapper.h"
#include "../HashMap/HashMapLinearProbing.h"
#include "../HashMap/HashMapSeparateChaining.h"
using namespace std;
const size_t N = 100;

#include <memory> // for std::allocator


template<typename T>
void bar(HashMapWrapper<T> *hm, vector<T> values, std::vector <T> noValues) {
    SECTION("Empty hashMap") {
        //Vérifier que la taille est nulle
        REQUIRE(!hm->size());
        for(T val : noValues){
            REQUIRE(!hm->contains(val));
            REQUIRE(!hm->erase(val));
        }
    }

    SECTION("Insert key (and contains)") {
        for(T val : values){
            hm->insert(val);
            REQUIRE(hm->contains(val));
        }

        REQUIRE(hm->size() == values.size());
    }

    SECTION("Remove key") {
        for(T val : values){
            hm->insert(val);
        }

        for(T val : values){
            hm->erase(val);
            REQUIRE(!hm->contains(val));
        }

        REQUIRE(!hm->size());
    }

    SECTION("Resize hashmap") {
        SECTION("Extend") {
            size_t M = hm->max_size();

            for(size_t N = 0; N < values.size(); ++N){
                double factor = (double)(N+1) / M;

                hm->insert(values.at(N));

                //std::cout << setw(2)<< N+1 << "|" << M << "|" <<  factor << endl;

                if(factor >= hm->getMaxFactor()){ // realloc expected
                    double actualFactor = (double)hm->size() / hm->max_size();

                    //std::cout << "\t" << hm.size() << " / " << hm.max_size() << " = " << actualFactor << endl;
                    REQUIRE(actualFactor == (factor / hm->getMaxCoefFactor()));
                    M = hm->max_size();
                }

            }

        }

        SECTION("Reduce") {
            for(T val: values)
                hm->insert(val);

            size_t M = hm->max_size();
            for(int N = hm->size() - 1; N >= 0; --N){
                hm->erase(values.at(N));
                double factor = (double)N/M;
                double actualFactor = (double)hm->size() / hm->max_size();
                //std::cout << setw(2)<< N << "|" << M << "|" <<  factor << endl;
                if(M == hm->getMinValueForM()){
                    REQUIRE((actualFactor == factor )); //TODO: Verifier nom
                }else if(factor <= hm->getMinFactor() ){ // realloc expected
                    //std::cout << "\t" << hm.size() << " / " << hm.max_size() << " = " << actualFactor << endl;
                    REQUIRE((actualFactor == (factor * hm->getMinCoefFactor()))); //TODO: Verifier nom
                    M = hm->max_size();
                }

            }

        }
    }
}

template<typename T>
void testString(HashMapWrapper<T> *hm){
    std::string fruits[] = {"pomme","poire","fraise","pasteque","orange","mandarine","citron","noix", "noisette", "melon"};
    const size_t SIZE_FRUITS = 10;
    std::string suppressFruits[] = {"poire","pasteque","mandarine","noix", "melon"};
    const size_t SIZE_SUPRESSED_FRUITS = 5;

    SECTION("New size, is 0") {
        REQUIRE(hm->size() == 0);
    }SECTION("insert all fruits, count and check if it is contained") {
        for (size_t i = 0; i < SIZE_FRUITS; ++i) {
            hm->insert(fruits[i]);
            REQUIRE(hm->size() == i + 1);
            //Check que les éléments ne s'insérent pas à double
            hm->insert(fruits[i]);
            REQUIRE(hm->size() == i + 1);
            REQUIRE(hm->contains(fruits[i]));
        }
        REQUIRE(!hm->contains("piment"));
    }SECTION("insert all fruits, erase some, count and check if it is contained") {

        for (size_t i = 0; i < SIZE_FRUITS; ++i)
            hm->insert(fruits[i]);

        for (size_t i = 0; i < SIZE_SUPRESSED_FRUITS; ++i) {
            hm->erase(suppressFruits[i]);
            REQUIRE(hm->size() == SIZE_FRUITS - 1 - i);
            //Check que les éléments ne s'effacent pas deux fois
            hm->erase(suppressFruits[i]);
            REQUIRE(hm->size() == SIZE_FRUITS - 1 - i);
        }
        for (size_t i = 0; i < SIZE_FRUITS; ++i){
            if(!(i % 2))
                REQUIRE(hm->contains(fruits[i]));
            else
                REQUIRE(!hm->contains(fruits[i]));
        }
    }
}

template<typename T>
void testSize_t(HashMapWrapper<T> *hm){

    SECTION("New size, is 0") {
        REQUIRE(hm->size() == 0);
    }SECTION("size == i, i in [1,...,N], with insert") {
        for (size_t i = 1; i <= N; ++i) {
            hm->insert(i);
            REQUIRE(hm->size() == i);
            //Check que les éléments ne s'insérent pas à double
            hm->insert(i);
            REQUIRE(hm->size() == i);
        }
    }SECTION("contains == i, i in [1,...,N], with insert where elements are 2k, k in R") {

        for (size_t i = 1; i <= N; ++i) {
            if(i % 2)
                hm->insert(i);
        }

        for (size_t i = 1; i <= N; ++i) {
            if(i % 2)
                REQUIRE(hm->contains(i));
            else
                REQUIRE(!hm->contains(i));
        }
    }SECTION("size == i, i in [1,...,N], with erase") {
        for (size_t i = 1; i <= N; ++i) {
            hm->insert(i);
        }
        for (size_t i = 1; i <= N; ++i) {
            hm->erase(i);
            REQUIRE(hm->size() == N - i);
            //check que l'élément ne déjà effecé ne modifie rien
            hm->erase(i);
            REQUIRE(hm->size() == N - i);
        }
    }
    SECTION("contains == i, i in [1,...,N], with erase for elements that are 2k, k in R") {
        for (size_t i = 1; i <= N; ++i) {
            hm->insert(i);
            if(i % 2)
                hm->erase(i);
        }
        for (size_t i = 1; i <= N; ++i) {
            if(i % 2)
                REQUIRE(!hm->contains(i));
            else
                REQUIRE(hm->contains(i));
        }
    }
}
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

TEST_CASE("Linear Probing", "[hashmap]")
{


    const double MAX_FACTOR = 0.5;
    const double MIN_FACTOR = 1.0/8;



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
        HashMapLinearProbing<size_t> lb;
        auto* hw = reinterpret_cast<HashMapWrapper<size_t> *>(&lb);
        bar(hw, values, valuesExclude);

        HashMapLinearProbing<size_t> lb2;
        auto* hw2 = reinterpret_cast<HashMapWrapper<size_t> *>(&lb2);
        testSize_t(hw2);
    }

    SECTION("String values") {
        vector<string> values = {"H", "Salut", "Les amis", "Oui"};
        vector<string> valuesExclude = {"h", "tulaS", "Non", "Enjoy"};
        HashMapLinearProbing<string> lb;
        auto* hw = reinterpret_cast<HashMapWrapper<std::string> *>(&lb);
        bar(hw, values, valuesExclude);

        HashMapSeparateChaining<string> lb2;
        auto* hw2 = reinterpret_cast<HashMapWrapper<std::string> *>(&lb2);
        testString(hw2);
       /* HashMapSeparateChaining<string> sc;
        auto* hwSc = reinterpret_cast<HashMapWrapper<string> *>(&sc);
        bar(hwSc, values, valuesExclude);*/
   }




}
TEST_CASE("SeparateChaining", "[hashmap]"){
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

        HashMapSeparateChaining<size_t> sc;
        auto* hwSc = reinterpret_cast<HashMapWrapper<size_t> *>(&sc);
        bar(hwSc, values, valuesExclude);

        HashMapLinearProbing<size_t> sc2;
        auto* hw2 = reinterpret_cast<HashMapWrapper<size_t> *>(&sc2);
        testSize_t(hw2);
    }

    SECTION("String values") {
        vector<string> values = {"H", "Salut", "Les amis", "Oui"};
        vector<string> valuesExclude = {"h", "tulaS", "Non", "Enjoy"};
        HashMapSeparateChaining<string> sc;
        auto* hw = reinterpret_cast<HashMapWrapper<std::string> *>(&sc);
        bar(hw, values, valuesExclude);

        HashMapSeparateChaining<string> sc2;
        auto* hw2 = reinterpret_cast<HashMapWrapper<std::string> *>(&sc2);
        testString(hw2);
        /* HashMapSeparateChaining<string> sc;
         auto* hwSc = reinterpret_cast<HashMapWrapper<string> *>(&sc);
         bar(hwSc, values, valuesExclude);*/
    }
}

