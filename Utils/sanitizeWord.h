//
// Created by david on 23.01.21.
//

#ifndef ASD2_LABS_2020_SANITIZEWORD_H
#define ASD2_LABS_2020_SANITIZEWORD_H

#include <string>

std::string sanitizeWord(const std::string& w) {

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


#endif //ASD2_LABS_2020_SANITIZEWORD_H
