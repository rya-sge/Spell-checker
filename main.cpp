//
// Created by Antoine Rochat on 23.05.20.
//

#include <iostream>
#include "Dictionary.h"
#include "HashMap/HashMapWrapper.h"
#include "HashMap/HashMapLinearProbing.h"
#include "HashMap/HashMapSeparateChaining.h"

using namespace std;


std::string sanitizeWord(const std::string& w){

    std::string saneWord;
    for(char c : w){
        if(!isalpha(c) && c != '\'')
            continue; // skip non alpha and apostrophe
        else if(isupper(c))
            c = (char)tolower(c); // remove uppercase

        saneWord += c;

    }

    // loop needed in the case there are multiple apostrophes at the beginning/end character
    // i.e "'''''test'''''"
    bool apoFound = true;
    while(apoFound){
        if(saneWord.back() == '\'')
            saneWord.pop_back();
        else if(saneWord.front() == '\'')
            saneWord = saneWord.substr(1, saneWord.size() - 1);
        else
            apoFound = false;
    }

    return saneWord;

}


int main() {
    Dictionary<HashMapLinearProbing<string>> dico("../Labo4_data/dictionary.txt");

    cout << dico.contains("faraway") << endl;
    dico.print();

    return 0;
}