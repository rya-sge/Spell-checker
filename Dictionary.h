//
// Created by david on 23.12.20.
//

#ifndef ASD2_LABS_2020_DICTIONARY_H

#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iostream>

template<typename Container>
class Dictionary{
    Container* words;

private:
    std::string sanitizeWord(const std::string& w) const {

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
public:

    Dictionary(Container& container,const std::string& inputfile) : words(&container){

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
