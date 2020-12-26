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
#include "SpellChecker.h"
using namespace std;

#include <iostream>
#include <functional>
#include <unordered_set>

using namespace std;


int main() {
 /*   typedef string Type;
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
return 0;*/
    typedef HashMapLinearProbing<string> ContainerType;
    typedef C<string> ContainerWrapper;
    ContainerType test;


    ContainerWrapper us ([&test](const string& key){ return test.contains(key);},
                         [&test](const string& key){ test.insert(key);},
                         [&test](const string& key){ test.erase(key);});


    const string DICTIONARY_FILE ="../Labo4_data/dictionary.txt";
    const string INPUT_FILE = "../Labo4_data/input_simple.txt";


    const Dictionary<ContainerWrapper> DICO(us, DICTIONARY_FILE);
    SpellChecker<ContainerWrapper> sp(INPUT_FILE, DICO);

    string res = sp.result();
    cout << res << endl;
    //sp.writeOutput("../output.txt");

    cout << "done" << endl;
    return 0;
}

