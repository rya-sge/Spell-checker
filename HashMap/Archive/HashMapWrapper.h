#ifndef HASHMAP_WRAPPER_H
#define HASHMAP_WRAPPER_H

#include <unordered_set>

template<typename T>
class HashMapWrapper {

    std::unordered_set<T> hashMap;

public:

    void insert(const T& key) {
        hashMap.insert(key);
    }

    bool contains(const T& key) {
        return hashMap.find(key) != hashMap.end();
    }

    void erase(const T& key) {
        hashMap.erase(key);
    }

    size_t size() {
        return hashMap.size();
    }
};

#endif //HASHMAP_WRAPPER_H
