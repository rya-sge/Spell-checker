/* ---------------------------
Laboratoire : 8 - Correcteur orthographique
Fichier : Dictionary.h
Auteurs : David Pellissier, Michael Ruckstuhl, Ryan Sauge
Date : 23.01.2021

But : Implémentation d'un dictionnaire utilisé pour le correcteur orthographique

Compilateur : gcc 9.3.0
--------------------------- */

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
     * @param Container offrant les méthodes suivantes: insert, contains, erase
     */
    Dictionary(ContainerType& container) : words(&container) {};

    /**
     * @brief Crée le dictionnaire en le remplissant en lisant les mots contenus dans inputfile
     * @param Container offrant les méthodes suivantes: insert, contains, erase
     * @param inputfile fichier à lire
     */
    Dictionary(ContainerType& container, const std::string& inputfile) : words(&container){

        // Lecture
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

            // Ajout de tous les mots
            while(getline(iss, token, ' ')){
                addWord(token);
            }

        }

        file.close();
    }

    /**
     * @brief Ajout un mot (word) dans le dictionnaire
     * @param word
     */
    void addWord(std::string word){
        word = sanitizeWord(word);
        words->insert(word);
    }

    /**
     * @brief Supprime un mot du dictionnaire
     * @param word
     */
    void eraseWord(std::string word){
        return words->erase(word);
    }

    /**
     * @param word
     * @return true si le mot existe dans le dicionnaire
     */
    bool contains(std::string word) const{
        word = sanitizeWord(word);
        return words->contains(word);
    }

    /**
     * @brief retourne le nombre de mots dans le dictionnaire
     */
    size_t size() const {
        return words->size();
    }


};
#define ASD2_LABS_2020_DICTIONARY_H

#endif //ASD2_LABS_2020_DICTIONARY_H
