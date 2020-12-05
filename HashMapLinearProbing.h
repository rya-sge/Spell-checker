#ifndef ASD2_LABS_2020_HASHMAPLINEARPROBING_H
#define ASD2_LABS_2020_HASHMAPLINEARPROBING_H

#include <cstdlib>
#include <vector>

template<typename T>
class HashMapLinearProbing {
// Valeurs par défaut
    size_t M = 2;
    size_t N = 0;
    double MAX_FACTOR = 0.5;
    double MIN_FACTOR = (double)1/8;

    typedef std::vector<T> HashMap;
    HashMap hashMap;



    const size_t EMPTY_VALUE = 0;

private:
    size_t hash(const T& key) {
        return std::hash<T>()(key) % M;
    }



public:

    void insert(const T& key) {
        if((double)N / M >= MAX_FACTOR){
            // todo realloc
        }

        // find first available index
        size_t index = hash(key);
        while(hashMap.at(index) != EMPTY_VALUE && hashMap.at(index) != key){
                index = (index + 1)%M;
        }
        hashMap.at(index) = key;
    }

    bool contains(const T& key) {
        size_t index = hash(key);
        size_t count = 0;

        while(count != N){
            if(hashMap.at(index) == key)
                return true;
            else if(!hashMap.at(index))
                break;

            index = (index + 1)%M;
            ++count;
        }

    }

    void erase(const T& key) {

    }

    size_t size() {
        return N;
    }
};



#endif //ASD2_LABS_2020_HASHMAPLINEARPROBING_H
