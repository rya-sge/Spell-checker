
// Needed
#include "Dictionary.h"
#include "SpellChecker.h"
#include "HashMap/Container.h"
#include <iostream>
#include <chrono>

// For Testing
#include "HashMap/HashMapLinearProbing.h"
#include "HashMap/HashMapSeparateChaining.h"
#include "TernarySearchTree.h"

#include <unordered_set>
#include "AVLTree.h"

using namespace std;


int main() {
    const string DICTIONARY_FILE ="../Labo4_data/dictionary.txt";
    const string INPUT_FILE = "../Labo4_data/input_wikipedia.txt";

    typedef C<string> ContainerWrapper;

    // INFO : Pour tester, simplement enlever le "/*" du le titre de la section

    /*// LINEAR PROBING
    typedef HashMapLinearProbing<string> ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){ return test.contains(key);},
                         [&test](const string& key){ test.insert(key);},
                         [&test](const string& key){ test.erase(key);}); //*/

    /*// SEPARATE CHAINING
    typedef HashMapLinearProbing<string> ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){ return test.contains(key);},
                         [&test](const string& key){ test.insert(key);},
                         [&test](const string& key){ test.erase(key);}); //*/

    // VECTEUR
    typedef vector<string> ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){ return binary_search(test.begin(), test.end(), key) ;},
                         [&test](const string& key){ test.insert(upper_bound(test.begin(), test.end(), key), key); },
                         [&test](const string& key){ auto place = test.erase(lower_bound(test.begin(), test.end(), key));}
                         ); //*/

    /*// AVL
    typedef AVLTree<string, char> ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){ return test.contains(key);},
                         [&test](const string& key){ test.put(key, 0);},
                         [&test](const string& key){ test.deleteElement(key);}); //*/

    /*// TST
    typedef TST ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){return test.contains(key);},
                         [&test](const string& key){ test.put(key, 1);},
                         [&test](const string& key){ }); //*/


    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE);

    chrono::high_resolution_clock::time_point  begin = chrono::high_resolution_clock::now();
    SpellChecker<ContainerWrapper> sp(INPUT_FILE, DICO);

    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long double time = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

    string res = sp.result();
    cout << res << endl;
    //sp.writeOutput("../output.txt");

    cout << "done in " << time << "ms" << endl;
    return 0;
}