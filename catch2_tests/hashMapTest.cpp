#include <iostream>
#include "catch.hpp"
#include "../HashMap/HashMapWrapper.h"
#include "../HashMap/HashMapLinearProbing.h"
#include "../HashMap/HashMapSeparateChaining.h"

using namespace std;

const size_t SIZE_VECTOR_TEST = 20;
const size_t N = 100;

#include <memory> // for std::allocator


template<typename T>

/**
 *
 * @tparam T
 * @param hm
 * @param values
 * @param noValues
 * @details test Empty hashMap, insert and contains, erase, resize, reduce with specified vectors
 *
 */
void testCommonGeneral(HashMapWrapper<T> *hm, vector<T> values, std::vector<T> noValues) {
    SECTION("Empty hashMap") {
        REQUIRE(!hm->size());
        for (T val : noValues) {
            REQUIRE(!hm->contains(val));
            REQUIRE(!hm->erase(val));
        }
    }

    SECTION("Insert key (and contains)") {
        for (T val : values) {
            hm->insert(val);
            REQUIRE(hm->contains(val));
        }

        REQUIRE(hm->size() == values.size());
    }

    SECTION("Erase key") {
        for (T val : values) {
            hm->insert(val);
        }

        for (T val : values) {
            hm->erase(val);
            REQUIRE(!hm->contains(val));
        }

        REQUIRE(!hm->size());
    }

    SECTION("Resize hashmap") {
        SECTION("Extend") {
            size_t M = hm->max_size();

            for (size_t N = 0; N < values.size(); ++N) {
                double factor = (double) (N + 1) / M;

                hm->insert(values.at(N));

                if (factor >= hm->getMaxFactor()) { // realloc expected
                    double actualFactor = (double) hm->size() / hm->max_size();
                    REQUIRE(actualFactor == (factor / hm->getMaxCoefFactor()));
                    M = hm->max_size();
                }

            }

        }

        SECTION("Reduce") {
            for (T val: values)
                hm->insert(val);

            size_t M = hm->max_size();
            for (int n = hm->size() - 1; n >= 0; --n) {
                hm->erase(values.at(n));
                double factor = (double) n / M;
                double actualFactor = (double) hm->size() / hm->max_size();
                if (M == hm->getMinValueForM()) {
                    REQUIRE((actualFactor == factor));
                } else if (factor <= hm->getMinFactor()) { // realloc expected
                    REQUIRE((actualFactor == (factor * hm->getMinCoefFactor())));
                    M = hm->max_size();
                }

            }

        }
    }
}

/**
 *
 * @tparam T
 * @param hm
 * @param n number of elements used for test hashmap
 * @details test size, insert and contains, erase with a specific size
 */
template<typename T>
void testCommonSize(HashMapWrapper<T> *hm, size_t n) {
    SECTION("New size, is 0") {
        REQUIRE(hm->size() == 0);
    }SECTION("size == i, i in [1,...,n], with insert") {
        for (size_t i = 1; i <= n; ++i) {
            hm->insert(i);
            REQUIRE(hm->size() == i);
            //Check que les éléments ne s'insérent pas à double
            hm->insert(i);
            REQUIRE(hm->size() == i);
        }
    }SECTION("contains == i, i in [1,...,n], with insert where elements are 2k, k in R") {

        for (size_t i = 1; i <= n; ++i) {
            if (i % 2)
                hm->insert(i);
        }

        for (size_t i = 1; i <= n; ++i) {
            if (i % 2)
                REQUIRE(hm->contains(i));
            else
                REQUIRE(!hm->contains(i));
        }
    }SECTION("size == i, i in [1,...,n], with erase") {
        for (size_t i = 1; i <= n; ++i) {
            hm->insert(i);
        }
        for (size_t i = 1; i <= n; ++i) {
            hm->erase(i);
            REQUIRE(hm->size() == n - i);
            //check qu'il n'ait aucune modification quand on supprime un élément déjà supprimé.
            hm->erase(i);
            REQUIRE(hm->size() == n - i);
        }
    }SECTION("contains == i, i in [1,...,n], with erase for elements that are 2k, k in R") {
        for (size_t i = 1; i <= n; ++i) {
            hm->insert(i);
            if (i % 2)
                hm->erase(i);
        }
        for (size_t i = 1; i <= n; ++i) {
            if (i % 2)
                REQUIRE(!hm->contains(i));
            else
                REQUIRE(hm->contains(i));
        }
    }
}

/**
 *
 * @tparam T
 * @param hm
 * @details test  with strings
 */
template<typename T>
void testCommonString(HashMapWrapper<T> *hm) {
    std::string fruits[] = {"pomme", "poire", "fraise", "pasteque", "orange", "mandarine", "citron", "noix", "noisette",
                            "melon"};
    const size_t SIZE_FRUITS = 10;
    std::string suppressFruits[] = {"poire", "pasteque", "mandarine", "noix", "melon"};
    const size_t SIZE_SUPRESSED_FRUITS = 5;

    SECTION("New size, is 0") {
        REQUIRE(hm->size() == 0);
    }SECTION("Insert all fruits, count and check if it is contained") {
        for (size_t i = 0; i < SIZE_FRUITS; ++i) {
            hm->insert(fruits[i]);
            REQUIRE(hm->size() == i + 1);
            //Check que les éléments ne s'insérent pas à double
            hm->insert(fruits[i]);
            REQUIRE(hm->size() == i + 1);
            REQUIRE(hm->contains(fruits[i]));
        }
        REQUIRE(!hm->contains("piment"));
    }SECTION("Insert all fruits, erase some, count and check if it is contained") {

        for (size_t i = 0; i < SIZE_FRUITS; ++i)
            hm->insert(fruits[i]);

        for (size_t i = 0; i < SIZE_SUPRESSED_FRUITS; ++i) {
            hm->erase(suppressFruits[i]);
            REQUIRE(hm->size() == SIZE_FRUITS - 1 - i);
            //Check que les éléments ne s'effacent pas deux fois
            hm->erase(suppressFruits[i]);
            REQUIRE(hm->size() == SIZE_FRUITS - 1 - i);
        }
        for (size_t i = 0; i < SIZE_FRUITS; ++i) {
            if (i % 2)
                REQUIRE(!hm->contains(fruits[i]));
            else
                REQUIRE(hm->contains(fruits[i]));

        }
    }
}


/**
 * @brief prepare vector for test
 * @param values
 * @param valuesExclude
 */
void prepareVector(vector<size_t> &values, vector<size_t> &valuesExclude) {
    for (unsigned i = 0; i < values.size(); ++i) {
        values.at(i) = i;
    }
    for (unsigned elem = values.size(), i = 0; i < valuesExclude.size(); ++i, ++elem) {
        valuesExclude.at(i) = elem;
    }
}

/**
 * test CASE for Linear Probing
 */
TEST_CASE("Linear Probing", "[hashmap]") {
    SECTION("Size_T values") {
        vector<size_t> values(SIZE_VECTOR_TEST);
        vector<size_t> valuesExclude(SIZE_VECTOR_TEST);
        prepareVector(values, valuesExclude);

        HashMapLinearProbing<size_t> lb;
        auto *hw = reinterpret_cast<HashMapWrapper<size_t> *>(&lb);
        testCommonGeneral(hw, values, valuesExclude);

        HashMapLinearProbing<size_t> lb2;
        auto *hw2 = reinterpret_cast<HashMapWrapper<size_t> *>(&lb2);
        testCommonSize(hw2, N);
    }

    SECTION("String values") {
        vector<string> values = {"H", "Salut", "Les amis", "Oui"};
        vector<string> valuesExclude = {"h", "tulaS", "Non", "Enjoy"};
        HashMapLinearProbing<string> lb;
        auto *hw = reinterpret_cast<HashMapWrapper<std::string> *>(&lb);
        testCommonGeneral(hw, values, valuesExclude);

        HashMapLinearProbing<string> lb2;
        auto *hw2 = reinterpret_cast<HashMapWrapper<std::string> *>(&lb2);
        testCommonString(hw2);
    }


}

/**
 * test CASE for Separate Chaining
 */
TEST_CASE("SeparateChaining", "[hashmap]") {
    SECTION("Size_T values") {
        vector<size_t> values(SIZE_VECTOR_TEST);
        vector<size_t> valuesExclude(SIZE_VECTOR_TEST);
        prepareVector(values, valuesExclude);

        HashMapSeparateChaining<size_t> sc;
        auto *hwSc = reinterpret_cast<HashMapWrapper<size_t> *>(&sc);
        testCommonGeneral(hwSc, values, valuesExclude);

        HashMapSeparateChaining<size_t> sc2;
        auto *hw2 = reinterpret_cast<HashMapWrapper<size_t> *>(&sc2);
        testCommonSize(hw2, N);
    }

    SECTION("String values") {
        vector<string> values = {"H", "Salut", "Les amis", "Oui"};
        vector<string> valuesExclude = {"h", "tulaS", "Non", "Enjoy"};

        HashMapSeparateChaining<string> sc;
        auto *hw = reinterpret_cast<HashMapWrapper<std::string> *>(&sc);
        testCommonGeneral(hw, values, valuesExclude);

        HashMapSeparateChaining<string> sc2;
        auto *hw2 = reinterpret_cast<HashMapWrapper<std::string> *>(&sc2);
        testCommonString(hw2);
    }
}

