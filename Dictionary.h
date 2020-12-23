//
// Created by david on 23.12.20.
//

#ifndef ASD2_LABS_2020_DICTIONARY_H

#include <string>


template<typename HashMap>
class Dictionary{
    HashMap words;

private:
    std::string sanitizeWord(const std::string& w){
        // todo: enlever les accents
    }

public:


    Dictionary(std::string inputfile){
        HashMap newWords;

        // read file
    }

    void addWord(std::string word){

    }

    bool eraseWord(std::string word){

    }

    bool contains(std::string word){

    }




};
#define ASD2_LABS_2020_DICTIONARY_H

#endif //ASD2_LABS_2020_DICTIONARY_H
