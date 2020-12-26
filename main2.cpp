//
// Created by super on 26/12/2020.
//

//
// Created by Antoine Rochat on 23.05.20.
//

#include <iostream>
#include "Dictionary.h"
#include "HashMap/HashMapWrapper.h"
#include "HashMap/HashMapLinearProbing.h"
#include "HashMap/HashMapSeparateChaining.h"

using namespace std;

#include <iostream>
#include <functional>
#include <unordered_set>

using namespace std;
template<typename Co, typename T>
class C{

    //Co container;

    //typedef std::function<bool(const T& key) const> boolFunction;
    // typedef std::function<void(const T& key) const> voidFunction;
    const  std::function<bool(const T& key)>& containsF;
    const  std::function<void(const T& key)>& insertF;
    const  std::function<void(const T& key)>& eraseF;

    // voidFunction &insertF;
    // voidFunction &eraseF;

public:
    /* C(const std::function<bool(const T& key)>& containsFunction) : containsF(containsFunction){

     }*/

    C(const std::function<bool(const T& key)>& containsFunction, const std::function<void(const T& key) >& insertFunction, const std::function<void(const T& key)> & eraseFunction)
            : containsF(containsFunction), insertF(insertFunction), eraseF(eraseFunction) {
        //this->container = container;
    }

    bool contains(const T& key) const{
        return containsF(key);
    }

    void insert(const T& key) const {
        insertF(key);
    }

    void erase(const T& key) const {
        eraseF(key);
    }
};




int main() {
    typedef string Type;
    typedef unordered_set<Type> Container;

    Container test;

    // C<Container, Type> d ([&test](const Type& key){ return test.find(key) != test.end();});

    C<Container, Type> us ([&test](const Type& key){ return test.find(key) != test.end();},
                           [&test](const Type& key){ test.insert(key);},
                           [&test](const Type& key){ test.erase(key);}       );

    return 0;
}

/*
