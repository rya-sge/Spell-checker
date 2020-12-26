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
#include "HashMap/Container.h"
using namespace std;

#include <iostream>
#include <functional>
#include <unordered_set>

using namespace std;


int main() {
    typedef string Type;
    typedef unordered_set<Type> Container;

    Container test;


    C<Type> us ([&test](const Type& key){ return test.find(key) != test.end();},
                           [&test](const Type& key){ test.insert(key);},
                           [&test](const Type& key){ test.erase(key);}       );

    test.insert("lol");
    cout << us.contains("lol");
    us.erase("lol");

    us.insert("Lol");
    us.erase("Lol");
    us.erase("V");
    us.contains("Lol");
return 0;
}

