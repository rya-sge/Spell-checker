

#ifndef ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H
#define ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H


#include <cstdlib>
#include <vector>
#include <forward_list>
#include <algorithm>

template<typename T>
class HashMapSeparateChaining {

    typedef std::forward_list<T> Bucket;
    typedef std::vector<Bucket> HashMap;
    HashMap hashMap;

    // Valeurs par défaut
    size_t M = 2;
    size_t N = 0;

private:
    size_t hash(T key) {
        return std::hash<T>()(key) % hashMap.size();
    }

public:


    void insert(const T& key) {

    }

    bool contains(const T& key) {
        size_t index = hash(key);
        return (std::find(hashMap.at(index).begin(), hashMap.at(index).end(), key) == hashMap.at(index).end());
    }

    void erase(const T& key) {

    }

    size_t size() {
        return N;
    }
};







#endif //ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H
