
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

    typedef Container<string> ContainerWrapper;

    chrono::high_resolution_clock::time_point begin, end;
    long double timeDico, timeSpellCheck;

    // Génération du dictionnaire
    begin = chrono::high_resolution_clock::now();

    // INFO : Pour tester, simplement enlever le "/*" du le titre de la section

    /*// LINEAR PROBING
    typedef HashMapLinearProbing<string> ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){ return test.contains(key);},
                         [&test](const string& key){ test.insert(key);},
                         [&test](const string& key){ test.erase(key);});
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE); //*/

    // SEPARATE CHAINING
    typedef HashMapLinearProbing<string> ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){ return test.contains(key);},
                         [&test](const string& key){ test.insert(key);},
                         [&test](const string& key){ test.erase(key);});
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE); //*/

    /*// VECTEUR
    typedef vector<string> ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){ return binary_search(test.begin(), test.end(), key) ;;},
                         [&test](const string& key){ test.push_back(key);},
                         [&test](const string& key){ test.erase(lower_bound(test.begin(), test.end(), key)); });

    // Lecture du fichier
    std::string line;
    std::ifstream file;

    file.open(DICTIONARY_FILE);

    if(!file.is_open()){
        std::cout << '\n' << "Erreur de lecture du fichier"; return EXIT_FAILURE;
    }
    while(!file.eof()){
        std::getline(file, line);
        std::istringstream iss(line);
        std::string word;
        while(getline(iss, word, ' ')){
            // add every word
            test.push_back(word);
        }
    }
    file.close();
    // Tri rapide
    sort(test.begin(), test.end());
    const Dictionary<ContainerWrapper> DICO(cw); //*/

    /*// AVL
    typedef AVLTree<string, char> ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){ return test.contains(key);},
                         [&test](const string& key){ test.put(key, 0);},
                         [&test](const string& key){ test.deleteElement(key);});
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE); //*/

    /*// TST
    typedef TST ContainerType;
    ContainerType test;
    ContainerWrapper cw ([&test](const string& key){return test.contains(key);},
                         [&test](const string& key){ test.put(key, 1);},
                         [&test](const string& key){ });
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE); //*/

    end = chrono::high_resolution_clock::now();
    timeDico = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    begin = chrono::high_resolution_clock::now();

    // Spellcheck
    SpellChecker<ContainerWrapper> sp(INPUT_FILE, DICO);
    string res = sp.result();
    cout << res << endl;
    //sp.writeOutput("../output.txt");


    end = chrono::high_resolution_clock::now();
    timeSpellCheck = chrono::duration_cast<chrono::milliseconds>(end - begin).count();


    cout << "Dictionary generated in " << timeDico << "ms" << endl;
    cout << "Spellcheck done in " << timeSpellCheck << "ms" << endl;
    cout << "Total time : " << timeDico + timeSpellCheck << "ms" << endl;

    return 0;
}