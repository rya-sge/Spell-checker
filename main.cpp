//
// Created by Antoine Rochat on 23.05.20.
//

#include <iostream>
#include "HashMapWrapper.h"

using namespace std;

template<typename T>
size_t hashFun(const T& key, size_t m) {
    return std::hash<T>()(key) % m;
}

int main() {

    //HashMapWrapper<std::string> hashMap;
    for(int i = 0; i < 10; ++i){
        size_t h = hashFun(i, 2);
        cout << i << " : " << h << endl;
    }
    //hashMap.insert("Hello world");
    return 0;
}