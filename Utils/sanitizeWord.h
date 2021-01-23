//
// Created by david on 23.01.21.
//

#ifndef ASD2_LABS_2020_SANITIZEWORD_H
#define ASD2_LABS_2020_SANITIZEWORD_H

#include <string>

/**
 * @brief Enlève les caractères spéciaux et les apostrophes aux extrémités du mot. Convertit le mot en minuscule
 * @param w mot à modifier
 * @return le mot en minuscules
 */
std::string sanitizeWord(const std::string& w) {

    std::string saneWord;
    for(char c : w){
        if(!isalpha(c) && c != '\'')
            continue; // supprime les caractères non alphabétiques qui ne sont pas des apostrophes
        else if(isupper(c))
            c = (char)tolower(c); // enlève les majuscules

        saneWord += c;

    }

    // boucle nécessaire pour le cas où il y a de multiples apostrophes au début ou à la fin du mot
    // par exemple: "'''''test'''''"
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
