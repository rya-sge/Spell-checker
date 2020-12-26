//
// Created by Antoine Rochat on 23.05.20.
//

#include <iostream>
#include <unordered_set>
#include "Dictionary.h"
#include "HashMap/HashMapLinearProbing.h"
#include "HashMap/HashMapSeparateChaining.h"
#include "SpellChecker.h"
#include "BinarySearchTree.h"
using namespace std;


int main() {
    using container = HashMapLinearProbing<string>;

    const string DICTIONARY_FILE ="../Labo4_data/dictionary.txt";
    const string INPUT_FILE = "../Labo4_data/input_simple.txt";

    const Dictionary<container> DICO(DICTIONARY_FILE);
    SpellChecker<container> sp(INPUT_FILE, DICO);

    string res = sp.result();
    cout << res << endl;
    sp.writeOutput("../output.txt");

    cout << "done" << endl;
    return 0;
}