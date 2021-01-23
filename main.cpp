/* ---------------------------
Laboratoire : 8 - Correcteur orthographique
Fichier : main.cpp
Auteurs : David Pellissier, Michael Ruckstuhl, Ryan Sauge
Date : 23.01.2021

But : Tester l'implémentation du correcteur orthographique

Compilateur : gcc 9.3.0
--------------------------- */

#include "Dictionary.h"
#include "SpellChecker.h"
#include "HashMap/DictionaryContainer.h"
#include <iostream>
#include <chrono>

// Structures de test
#include <unordered_set>
#include "HashMap/HashMapLinearProbing.h"
#include "HashMap/HashMapSeparateChaining.h"
#include "TernarySearchTree.h"

using namespace std;

typedef DictionaryContainer<string> ContainerWrapper;


// Prototypes des fonctions pour pouvoir les retrouver plus facilement
void testCommon(const string &INPUT_FILE, const Dictionary<ContainerWrapper> &DICO, long double timeDico, bool sansAffichage = false);
void testLinearProbing(const string&INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage = false);
void testSeparateChaining(const string&INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage = false);
void testUnorderedSet(const string& INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage = false);
void testSortedVector(const string& INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage = false);
void testTST(const string& INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage = false);
void testAll(const string& INPUT_FILE, const string& DICTIONARY_FILE);

int main() {
    const string DICTIONARY_FILE ="../Labo4_data/dictionary.txt";
    const string INPUT_FILE = "../Labo4_data/input_sh.txt";

    // Comparaison de tous les tests (sans affichage du résultat)
    testAll(INPUT_FILE, DICTIONARY_FILE);

    // Tests avec affichage du résultat. Décommenter si nécessaire
    // testLinearProbing(INPUT_FILE, DICTIONARY_FILE);
    // testSeparateChaining(INPUT_FILE, DICTIONARY_FILE);
    // testUnorderedSet(INPUT_FILE, DICTIONARY_FILE);
    // testSortedVector(INPUT_FILE, DICTIONARY_FILE);
    // testTST(INPUT_FILE, DICTIONARY_FILE);

    return 0;
}

void testAll(const string &INPUT_FILE, const string &DICTIONARY_FILE){
    const bool SANS_AFFICHAGE = true;

    cout << "****Resultat****" << endl;
    cout << "**Sondage lineaire**" << endl;

    testLinearProbing(INPUT_FILE, DICTIONARY_FILE, SANS_AFFICHAGE);

    cout << endl << "**Par chainage**" << endl;
    testSeparateChaining(INPUT_FILE, DICTIONARY_FILE, SANS_AFFICHAGE);
    cout << endl << "**Unordered_Set**" << endl;
    testUnorderedSet(INPUT_FILE, DICTIONARY_FILE, SANS_AFFICHAGE);
    cout << endl << "**Vecteur trié**" << endl;
    testSortedVector(INPUT_FILE, DICTIONARY_FILE, SANS_AFFICHAGE);
    cout << endl << "**TST**" << endl;
    testTST(INPUT_FILE, DICTIONARY_FILE, SANS_AFFICHAGE);
}

/**
 * @param INPUT_FILE
 * @param DICO
 * @param timeDico
 */
void testCommon(const string &INPUT_FILE, const Dictionary<ContainerWrapper> &DICO, long double timeDico, bool sansAffichage){
    chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();

    // Spellcheck
    SpellChecker<ContainerWrapper> sp(INPUT_FILE, DICO);
    string res = sp.result();
    if(!sansAffichage){
        cout << res << endl;
    }

    // done
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long double timeSpellCheck = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

    cout << "Dictionnaire généré en : " << timeDico << "ms" << endl;
    cout << "Correcteur orthographique réalisé en : " << timeSpellCheck << "ms" << endl;
    cout << "Temps total : " << timeDico + timeSpellCheck << "ms" << endl;
}

/**
 * @param INPUT_FILE
 * @param DICTIONARY_FILE
 */
void testLinearProbing(const string& INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage){
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


    testCommon(INPUT_FILE, DICO, timeDico, sansAffichage);
}

/**
 * @param INPUT_FILE
 * @param DICTIONARY_FILE
 */
void testSeparateChaining(const string& INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage){
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


    testCommon(INPUT_FILE, DICO, timeDico, sansAffichage);
}
/**
 * @param INPUT_FILE
 * @param DICTIONARY_FILE
 */
void testUnorderedSet(const string& INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage){
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


    testCommon(INPUT_FILE, DICO, timeDico, sansAffichage);
}

/**
 *
 * @param INPUT_FILE
 * @param DICTIONARY_FILE
 * @details
 *  Ici on insère les valeurs à la fin du vecteur puis on trie le vecteur.
    On peut se le permettre car on n'utilisera plus la fonction insert dans la suite des tests.
    À ne pas faire en pratique car le vecteur doit être trié en tout temps
    Pour la fonction insert, la bonne pratique serait de :
     -déterminer l'endroit où il faut insérer avec un appel à lower_bound
        auto it = std::lower_bound(test.begin(), test.end()) pour
    puis ensuite insérer la clé à la position trouvée :
        test.insert(it, key)
 */
void testSortedVector(const string& INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage){

    chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();

    // Creation
    vector<string> test;
    ContainerWrapper cw ([&test](const string& KEY){ return binary_search(test.begin(), test.end(), KEY) ;},
                         [&test](const string& KEY){ test.push_back(KEY);},
                         [&test](const string& KEY){ test.erase(lower_bound(test.begin(), test.end(), KEY)); });
    const Dictionary<ContainerWrapper> DICO(cw, DICTIONARY_FILE);
    sort(test.begin(), test.end());

    // done
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    long double timeDico = chrono::duration_cast<chrono::milliseconds>(end - begin).count();


    testCommon(INPUT_FILE, DICO, timeDico, sansAffichage);
}

/**
 * @param INPUT_FILE
 * @param DICTIONARY_FILE
 */
void testTST(const string& INPUT_FILE, const string& DICTIONARY_FILE, bool sansAffichage){
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


    testCommon(INPUT_FILE, DICO, timeDico, sansAffichage);
}