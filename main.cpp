//
// Created by Antoine Rochat on 23.05.20.
//

#include <iostream>
#include "HashMapWrapper.h"
#include "HashMapSeparateChaining.h"

using namespace std;

template<typename T>
size_t hashFun(const T& key, size_t m) {
    return std::hash<T>()(key) % m;
}

int main() {

    HashMapWrapper<std::string> hashMap;

    hashMap.insert("Hello world");

    const size_t N = 100;
    HashMapSeparateChaining<size_t> sp;

    for (size_t i = 1; i <= N ; ++i) {
        sp.insert(i);
    }

    /*for (size_t i = 0; i <= N ; ++i) {
        cout << sp.size() << endl;
        sp.erase(N-i);
    }*/

    sp.erase(42);
    cout << sp.size() << endl;

    return 0;
}