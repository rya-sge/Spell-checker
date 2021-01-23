#ifndef ASD2_LABS_2020_HASHMAPLINEARPROBING_H
#define ASD2_LABS_2020_HASHMAPLINEARPROBING_H

#include <cstdlib>
#include <vector>
#include "HashMapWrapper.h"



template<typename T>
class HashMapLinearProbing : public HashMapWrapper<T> {


private:
    // Valeurs par défaut
    const size_t MIN_VALUE_M = 2;
    const double MAX_FACTOR = 1.0 / 2;
    const double MIN_FACTOR = 1.0 / 8;
    const size_t MAX_FACTOR_COEF = 2;
    const size_t MIN_FACTOR_COEF = 2;




    class HashNode {
    public:
        // V value;
        T key;

        //Constructor of hashnode
        HashNode(T key) {
            // this->value = value;
            this->key = key;
        }
    };

    typedef std::vector<HashNode *> HashMap;

    size_t M = MIN_VALUE_M;
    size_t N = 0;

    HashMap *hashMap;

    size_t hash(const T &key, size_t m) const{
        return std::hash<T>()(key) % m;
    }

    void findPosition(HashMap *hashMap, const T &key, size_t m, size_t &index) {
        while (hashMap->at(index) != NULL && hashMap->at(index)->key != key) {
            index = (index + 1) % m;
        }
    }

    void realloc(size_t newM) {
        HashMap *newHashMap = new HashMap(newM);

        for (HashNode *ptr: *hashMap) {
            if (ptr != NULL) {
                T key = ptr->key;
                // insert values into the new table
                size_t index = hash(key, newM);
                findPosition(newHashMap, key, newM, index);
                newHashMap->at(index) = ptr;
            }

        }

        HashMap *oldHashMap = hashMap;
        hashMap = newHashMap;
        delete oldHashMap;

        M = newM;
    }

public:

    HashMapLinearProbing() {
        hashMap = new HashMap(M);
    }

/*  // Constructeur de copie: pas utile mais je le laisse au cas où
    HashMapLinearProbing(const HashMapLinearProbing<T>& copy){
        hashMap = new DictionaryContainer(copy.M);
        for (int i = 0; i < copy.N; ++i) {
            HashNode *ptr = copy.hashMap->at(i);
            if(ptr != NULL){
                hashMap->at(i) = ptr;
            }
        }

        M = copy.M;
        N = copy.N;
    }
*/

    ~HashMapLinearProbing() {
        for (HashNode *ptr : *hashMap) {

            delete ptr;
        }
        delete hashMap;
        hashMap = NULL;
    }

    void insert(const T &key) {
        // find first available index
        if (contains(key))
            return;

        size_t index = hash(key, M);
        findPosition(hashMap, key, M, index);
        hashMap->at(index) = new HashNode(key);
        ++N;

        if ((double) N / M >= MAX_FACTOR) {
            realloc(M * 2);
        }
    }

    bool contains(const T &key) const{
        size_t index = hash(key, M);
        size_t count = 0;

        while (count != N) {
            if (hashMap->at(index) != NULL && hashMap->at(index)->key == key)
                return true;
            else if (!hashMap->at(index))
                break;

            index = (index + 1) % M;
            ++count;
        }

        return false;
    }

    bool erase(const T &key) {
        if (!contains(key)) return false;
        int i = hash(key, M);
        while (hashMap->at(i) == NULL || hashMap->at(i)->key != key) {
            i = (i + 1) % M;
        }
        delete hashMap->at(i); //Suppression objet pointé
        hashMap->at(i) = NULL;
        i = (i + 1) % M;
        while (hashMap->at(i) != NULL) {
            T keyToRedo = hashMap->at(i)->key;
            //Value valToRedo = vals[i];
            delete hashMap->at(i); //Suppression objet pointé
            hashMap->at(i) = NULL;
            // vals[i] = null;
            N--;
            insert(keyToRedo);
            i = (i + 1) % M;

        }
        --N;
        if (M > MIN_VALUE_M && (double) N / M <= MIN_FACTOR) {
            realloc(M / MAX_FACTOR_COEF);
        }
        return true;
    }

    size_t size() const{
        return N;
    }

    size_t max_size() const {
        return M;
    }

    double getMaxFactor() const{
        return MAX_FACTOR;
    }

    double getMinFactor() const{
        return MIN_FACTOR;
    }

    size_t getMaxCoefFactor() const{
        return MAX_FACTOR_COEF;
    }

    size_t getMinCoefFactor() const{
        return MIN_FACTOR_COEF;
    }

    size_t getMinValueForM() const{
        return MIN_VALUE_M;
    }
};


#endif //ASD2_LABS_2020_HASHMAPLINEARPROBING_H
