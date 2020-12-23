

#ifndef ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H
#define ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H


#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
#include "HashMapWrapper2.h"

template<typename T>
class HashMapSeparateChaining : public HashMapWrapper2<T> {

    typedef std::list<T> Bucket;
    typedef std::vector<Bucket> HashMap;
private:
    HashMap hashMap;
    const size_t MIN_VALUE_M = 2;
    // Valeurs par défaut
    size_t M = MIN_VALUE_M;
    size_t N = 0;

    const double MAX_FACTOR = 8;
    const double MIN_FACTOR = 2;

    const double MIN_FACTOR_COEF = 2;
    const double MAX_FACTOR_COEF = 2;

    size_t hash(T key, size_t m) {
        return std::hash<T>()(key) % m;
    }

    void realloc(size_t newM){
        size_t hashCalcul;
        HashMap hashMapNew(newM);
        for (size_t i = 0; i < M; ++i)  {
            for (auto j = hashMap.at(i).begin(); j != hashMap.at(i).end(); ++j) {
                T k = *j;
                hashCalcul = hash(k, newM);
                hashMapNew.at(hashCalcul).push_front(k);
            }
        }
        hashMap = hashMapNew;
        M = newM;
    }

public:

    HashMapSeparateChaining(){
        hashMap.resize(2);
    }


    void insert(const T &key) {

        if(contains(key))
            return;

        N++;
        size_t occupancy = N / M;

        if (occupancy >= MAX_FACTOR) {
            size_t Mnew = M * MIN_FACTOR_COEF;
            realloc(Mnew);
        }

        size_t hKey = std::hash<T>()(key) % M;

        hashMap.at(hKey).push_front(key);
    }

    bool contains(const T& key) {
        size_t index = hash(key, M);
        return (std::find(hashMap.at(index).begin(), hashMap.at(index).end(), key) != hashMap.at(index).end());
    }

    bool erase(const T& key) {
        size_t index = hash(key, M);
        //peut-être utiliser contains:
        auto it = std::find(hashMap.at(index).begin(), hashMap.at(index).end(), key);
        if(it != hashMap.at(index).end()){
            hashMap.at(index).erase(it);
            --N;
            if(N / M <= MIN_FACTOR and M > 2){
                size_t Mnew = M / MAX_FACTOR_COEF;
                realloc( Mnew);
            }
        }else{
            return false;
        }
        return true;
    }

    size_t size() {
        return N;
    }
    size_t max_size() {
        return M;
    }

    double getMaxFactor() {
        return MAX_FACTOR;
    }

    double getMinFactor() {
        return MIN_FACTOR;
    }

    size_t getMaxCoefFactor() {
        return MAX_FACTOR_COEF;
    }

    size_t getMinCoefFactor() {
        return MIN_FACTOR_COEF;
    }
};

#endif //ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H
