//
// Created by david on 23.12.20.
//

#ifndef ASD2_LABS_2020_DICTIONARY_H

#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iostream>

#include "Utils/sanitizeWord.h"

template<typename ContainerType>
class Dictionary{
    ContainerType* words;

public:


    Dictionary(ContainerType& container) : words(&container) {};

    Dictionary(ContainerType& container, const std::string& inputfile) : words(&container){

        // read file
        std::string line;
        std::ifstream file;

        file.open(inputfile);

        if(!file.is_open()){
            std::cout << '\n' << "Erreur de lecture du fichier";
            return;
        }

        while(!file.eof()){
            std::getline(file, line);
            std::istringstream iss(line);
            std::string token;

            while(getline(iss, token, ' ')){
                // add every word
                addWord(token);
            }

        }

        file.close();
    }

    void addWord(std::string word){
        word = sanitizeWord(word);
        words->insert(word);
    }

    bool eraseWord(std::string word){
        return words->erase(word);
    }

    bool contains(std::string word) const{
        word = sanitizeWord(word);
        return words->contains(word);
    }

    void size() const {
        std::cout << words->size() << std::endl;
    }


};
#define ASD2_LABS_2020_DICTIONARY_H

#endif //ASD2_LABS_2020_DICTIONARY_H
