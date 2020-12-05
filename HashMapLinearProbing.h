#ifndef ASD2_LABS_2020_HASHMAPLINEARPROBING_H
#define ASD2_LABS_2020_HASHMAPLINEARPROBING_H

#include <cstdlib>
#include <vector>

template<typename T>
class HashMapLinearProbing {

    typedef std::vector<T> HashMap;
    HashMap hashMap;

    // Valeurs par défaut
    size_t M = 2;
    size_t N = 0;

    const size_t EMPTY_VALUE = 0;

private:
    size_t hash(const T& key) {
        return std::hash<T>()(key) % M;
    }

public:


    void insert(const T& key) {
        // TODO: check if rehash is needed

        size_t index = hash(key);
        // find first available index
        while(hashMap.at(index) != EMPTY_VALUE && hashMap.at(index) != key){
                index = (index + 1)%M;
        }
        hashMap.at(index) = key;


    }

    bool contains(const T& key) {
    }

    void erase(const T& key) {

    }

    size_t size() {
        return N;
    }
};



#endif //ASD2_LABS_2020_HASHMAPLINEARPROBING_H
