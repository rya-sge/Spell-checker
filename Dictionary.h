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


    /**
     * @param Container offering the following methods: insert, contains, erase
     */
    Dictionary(ContainerType& container) : words(&container) {};

    /**
     *
     * @param Container offering the following methods: insert, contains, erase
     * @param inputfile to read
     * @details Create a dictionnary with the words present in the inputfile
     */
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

    /**
     * @brief add a word to dictionary
     * @param word
     */
    void addWord(std::string word){
        word = sanitizeWord(word);
        words->insert(word);
    }

    /**
     * @brief Deletes a word from the dictionary
     * @param word
     */
    void eraseWord(std::string word){
        return words->erase(word);
    }

    /**
     * @param word
     * @return true if the word exists in the dictionary
     */
    bool contains(std::string word) const{
        word = sanitizeWord(word);
        return words->contains(word);
    }

    /**
     * @brief returns the number of words in the dictionary
     */
    size_t size() const {
        return words->size();
    }


};
#define ASD2_LABS_2020_DICTIONARY_H

#endif //ASD2_LABS_2020_DICTIONARY_H
