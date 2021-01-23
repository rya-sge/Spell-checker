
// Needed
#include "Dictionary.h"
#include "SpellChecker.h"
#include "HashMap/DictionaryContainer.h"
#include <iostream>
#include <chrono>

// For Testing
#include "HashMap/HashMapLinearProbing.h"
#include "HashMap/HashMapSeparateChaining.h"
#include "TernarySearchTree.h"

#include <unordered_set>
using namespace std;
typedef DictionaryContainer<string> ContainerWrapper;


// Prototypes des fonctions pour pouvoir les retrouver plus facilement
void testCommon(const string &INPUT_FILE, const Dictionary<ContainerWrapper> &DICO, long double timeDico);
void testLinearProbing(const string& INPUT_FILE, const string& DICTIONARY_FILE);
void testSeparateChaining(const string& INPUT_FILE, const string& DICTIONARY_FILE);
void testUnorderedSet(const string& KEY, const string& DICTIONARY_FILE);
void testSortedVector(const string& INPUT_FILE, const string& DICTIONARY_FILE);
void testTST(const string& INPUT_FILE, const string& DICTIONARY_FILE);


int main() {
    const string DICTIONARY_FILE ="../Labo4_data/dictionary.txt";
    const string INPUT_FILE = "../Labo4_data/input_sh.txt";

    testSortedVector(INPUT_FILE, DICTIONARY_FILE);
    //testTST(INPUT_FILE, DICTIONARY_FILE);
    //testLinearProbing(INPUT_FILE, DICTIONARY_FILE);
    //testSeparateChaining(INPUT_FILE, DICTIONARY_FILE);
    //testUnorderedSet(INPUT_FILE, DICTIONARY_FILE);

    return 0;
}

void testCommon(const string &INPUT_FILE, const Dictionary<ContainerWrapper> &DICO, long double timeDico){
    chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();

    // Spellcheck
    SpellChecker<ContainerWrapper> sp(INPUT_FILE, DICO);
    string res = sp.result();

    cout << res << endl;
    //sp.writeOutput("../output.txt");

    // done
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long double timeSpellCheck = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

    cout << "Dictionary generated in " << timeDico << "ms" << endl;
    cout << "Spellcheck done in " << timeSpellCheck << "ms" << endl;
    cout << "Total time : " << timeDico + timeSpellCheck << "ms" << endl;
}

void testLinearProbing(const string& INPUT_FILE, const string& DICTIONARY_FILE){
    chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();

    // Creation
    HashMapLinearProbing<string> test;
    ContainerWrapper cw([&test](const string& KEY){ return test.contains(KEY);},
                        [&test](const string& KEY){ test.insert(KEY);},
                        [&test](const string& KEY){ test.erase(KEY);});
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE);

    // done
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long double timeDico = chrono::duration_cast<chrono::milliseconds>(end - begin).count();


    testCommon(INPUT_FILE, DICO, timeDico);
}

void testSeparateChaining(const string& INPUT_FILE, const string& DICTIONARY_FILE){
    chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();

    // Creation
    HashMapSeparateChaining<string> test;
    ContainerWrapper cw ([&test](const string& KEY){ return test.contains(KEY);},
                         [&test](const string& KEY){ test.insert(KEY);},
                         [&test](const string& KEY){ test.erase(KEY);});
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE);

    // done
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long double timeDico = chrono::duration_cast<chrono::milliseconds>(end - begin).count();


    testCommon(INPUT_FILE, DICO, timeDico);
}

void testUnorderedSet(const string& INPUT_FILE, const string& DICTIONARY_FILE){
    chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();

    // Creation
    unordered_set<string> test;
    ContainerWrapper cw ([&test](const string& KEY){ return test.find(KEY) != test.end();},
                         [&test](const string& KEY){ test.insert(KEY);},
                         [&test](const string& KEY){ test.erase(KEY);}       );
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE);

    //done
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long double timeDico = chrono::duration_cast<chrono::milliseconds>(end - begin).count();


    testCommon(INPUT_FILE, DICO, timeDico);
}

void testSortedVector(const string& INPUT_FILE, const string& DICTIONARY_FILE){
    // Ici on insère les valeurs à la fin du vecteur puis on trie le vecteur.
    // On peut se le permettre car on n'utilisera plus la fonction insert dans la suite des tests.
    // À ne pas faire en pratique ! (le vecteur doit être trié en tout temps)
    chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();

    // Creation
    vector<string> test;
    ContainerWrapper cw ([&test](const string& KEY){ return binary_search(test.begin(), test.end(), KEY) ;;},
                         [&test](const string& KEY){ test.push_back(KEY);},
                         [&test](const string& KEY){ test.erase(lower_bound(test.begin(), test.end(), KEY)); });
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE);
    sort(test.begin(), test.end());

    // done
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long double timeDico = chrono::duration_cast<chrono::milliseconds>(end - begin).count();


    testCommon(INPUT_FILE, DICO, timeDico);
}

void testTST(const string& INPUT_FILE, const string& DICTIONARY_FILE){
    chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();

    // Creation
    TST test;
    ContainerWrapper cw ([&test](const string& KEY){return test.contains(KEY);},
                         [&test](const string& KEY){ test.insert(KEY, 1);},
                         [&test](const string& KEY){ test.erase(KEY);});
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE);

    // done
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long double timeDico = chrono::duration_cast<chrono::milliseconds>(end - begin).count();


    testCommon(INPUT_FILE, DICO, timeDico);
}